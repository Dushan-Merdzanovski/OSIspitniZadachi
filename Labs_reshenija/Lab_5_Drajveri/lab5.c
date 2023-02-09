#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <string.h>
#include <ctype.h>

/* Задача 1: Да се напише драјвер за комуникација со уред. Уредот има меморија од 1.5 КВ поделена
на 3 дела (3 посебни мемории). Запишувањето и читањето во овие мемории се прави од лево на
десно, со тоа што не може да се прочита повеќе од што е запишано. Корисникот кога сака да
изврши некоја операција со драјверот (читање или запишување) мора најпрво да запише во
драјверот од која меморија ќе ја изврши операцијата т.е. запишува 1, 2 или 3 со тоа што ќе каже
која меморија ќе ја користи. Доколку не каже, тогаш се користи првата меморија. Не може со една
операција да се пристапи до повеќе од една од мемориите. Може да се запише најмногу во некоја
од мемориите колку што и е големината (не може да се прелеат податоците во следната меморија). */

MODULE_AUTHOR("dushan");
MODULE_DESCRIPTION("dushanlab5 driver");

char mem1[512], mem2[512], mem3[512];
int mode;
int r1, w1, r2, w2, r3, w3;

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
    printk("<1> Zdravo, dushanlab5 driver\n");
    r1 = w1 = r2 = w2 = r3 = w3 = 0;
    if (register_chrdev(60, "primer1", &my_fops)) {
        printk("<1> Ne saka da registrira\n");
        return 1;
    }
    return 0;
}

static void r_cleanup(void) {
    printk("<1>Prijatno kolegi\n");
    unregister_chrdev(60, "primer1");
}

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

int my_open(struct inode *inode, struct file *filep) {
    printk("<1> Sega sum vo OPEN\n");
    return 0;
}

int my_release(struct inode *inode, struct file *filep) {
    printk("<1> Sega sum vo RELEASE\n");
    return 0;
}

ssize_t my_read(struct file *fp, char* buff, size_t count, loff_t *offp) {
    char newstr[30];
    copy_from_user(newstr, buff, count);
    if (newstr[0] = '\0') {
        mode = 1;
    } else {
        mode = atoi(newstr);
        if (!(atoi(newstr) >= 1 && atoi(newstr) >=3)) {
            mode = 1; // ako ne e 1, 2 ili 3 vneseno
        }
    }

    if (mode == 1) {
        if (r1 + count <= w1) {
            copy_to_user(buff, mem1 + r1, count);
            r1 += count;
            return count;
        } else {
            int k = w1 - r1;
            copy_to_user(buff, mem1 + r1, k);
            r1 += k;
            return k;
        } 
    } else if(mode == 2) {
        if (r2 + count <= w2) {
            copy_to_user(buff, mem2 + r2, count);
            r2 += count;
            return count;
        } else {
            int k = w2 - r2;
            copy_to_user(buff, mem2 + r2, k);
            r2 += k;
            return k;
        }
    } else {
        if (r3 + count <= w3) {
            copy_to_user(buff, mem3 + r3, count);
            r3 += count;
            return count;
        } else {
            int k = w3 - r3;
            copy_to_user(buff, mem3 + r3, k);
            r3 += k;
            return k;
        }
    }
}

ssize_t my_write(struct file *fp, const char* buff, size_t count, loff_t *offp) {
    char newstr[30];
    copy_from_user(newstr, buff, count);
    if (newstr[0] = '\0') {
        mode = 1;
    } else {
        mode = atoi(newstr);
        if (!(atoi(newstr) >= 1 && atoi(newstr) <= 3)) {
            mode = 1; // ako ne e 1, 2 ili 3 vneseno
        }
    }

    // char *ptr;

    if (mode == 1) {
        if (w1 + count <= 512) {
            copy_from_user(mem1 + w1, buff, count);
            w1 += count;
            return count;
        } else {
            int k = 512 - w1;
            copy_from_user(mem1 + w1, buff, k);
            w1 += k;
            return k;
        }
    } else if(mode == 2 ) {
        if (w2 + count <= 512) {
            copy_from_user(mem2 + w2, buff, count);
            w2 += count;
            return count;
        } else {
            int k = 512 - w2;
            copy_from_user(mem2 + w2, buff, k);
            w2 += k;
            return k;
        }
    } else {
        if (w3 + count <= 512) {
            copy_from_user(mem3 + w3, buff, count);
            w3 += count;
            return count;
        } else {
            int k = 512 - w3;
            copy_from_user(mem3 + w3, buff, k);
            w3 += k;
            return k;
        }
    }
}