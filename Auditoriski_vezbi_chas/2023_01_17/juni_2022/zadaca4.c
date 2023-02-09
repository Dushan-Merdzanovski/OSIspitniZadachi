#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <string.h>
#include <ctype.h>

// ZADACHA DRAJVERI JUNI 2022

/* 4.Да се напише драјвер за комуникација со уред. Уредот има меморија од 1КВ. Податоците во меморијата
се заклучени иницијално со 2 клучеви така што меморијата мора да се отклучи пред истата да се користи.
Доколку меморијата е заклучена не може да се чита ниту да се запишува во драјверот. За отклучување, во
драјверот мора да се запише првин клучот, па доколку е точен, следната операција кон драјверот е
овозможена. Првиот клуч има вредност „juni123“, додека пак, вториот клуч има вредност „juni!@#“.
Доколку се запише првиот клуч, драјверот е отклучен само за една операција после клучот, и после
повторно е заклучен истиот. Доколку се запише вториот клуч, драјверот е отклучен за повеќе операции
после тоа, т.е. е отворен за операции додека повторно не се запише вториот клуч во драјверот. */

char mem[1024]; // 1KB
char kluc1[8];
char kluc2[8];
// mozhesh so edna promenliva ova sve 0, 1 i 2 vrednosti da ima, 0 da e isto zaklucena, a drugite otvorena so kluc 1 ili kluc 2
int open; // 0 - zaklucen, 1 - otklucen
int key; // 1- kluc1, 2 - kluc2
int w;

static int r_init(void);
static void r_cleanup(void);
module_init(r_init);
module_exit(r_cleanup);

int my_open(struct inode *inode, struct file *filep);
int my_release(struct inode *inode, struct file *filep);
ssize_t my_read(struct file *filep, char *buff, size_t count, loff_t *offp);
ssize_t my_write(struct file *filep, const char *buff, size_t count, loff_t *offp);
struct file_operations my_fops = {
    open : my_open,
    read : my_read,
    write : my_write,
    release : my_release,
};

static int r_init(void) {
    printk("<1> Zdravo, ninji\n");
    
    strcpy(kluc1, "juni123");
    strcpy(kluc2, "juni!@#");
    key = 0;
    open = 0;
    w = 0;

    if (register_chrdev(60, "primer1", &my_fops)) {
        printk("<1> Ne saka da registrira\n");
        return 1;
    }
    return 0;
}

static void r_cleanup(void) {
    printk("<1>Sayonara\n");
    unregister_chrdev(60, "primer1");
}

ssize_t my_read(struct file *fp, char* buff, size_t count, loff_t *offp) {
    if (open == 1) { // otvoren drajverot
        int r;
        if (w >= count) {
            r = count;
        } else {
            r = w;
        }
        copy_to_user(buff, mem + w - r, r);
        if (key == 1) {
            open = 0;
            key = 0;
        }
        return r;
    } else { // zatvoren drajverot open == 0
        return 0;
    }
}

ssize_t my_write(struct file *fp, const char* buff, size_t count, loff_t *offp) {
    char kluc[8];
    int skip  = 0;
    if (open == 0) {
        copy_from_user(kluc, buff, 8);
        if (strcmp(kluc, kluc1) == 0) {
            open = 1;
            key = 1;
            return 0;
        } else if (strcmp(kluc,kluc2) == 0) {
            open = 1;
            key = 2;
            return 0;
        } else {
            return 0; // ne dozvoluvame nishto da pravi vo drajverot
        }
    } else {
        if (key == 2) {
            char kluc[8];
            copy_from_user(kluc, buff, 8);
            if (strcmp(kluc, kluc2) == 0) {
                open = 0;
                key = 0;
                return 0;
            } else {
                skip = 8;
                strcpy(mem + w, kluc, 8);
                w+=8;
            }
        }
        int r;
        if (1024 - w >= count-skip) { // (w + count - skip <= 1024)
            r = count - skip;
        } else {
            r = 1024 - w;
        }
        copy_from_user(mem + w, buff + skip, r);
        if (key == 1) {
            open = 0;
            key = 0;
        }
        return r;
    }
}