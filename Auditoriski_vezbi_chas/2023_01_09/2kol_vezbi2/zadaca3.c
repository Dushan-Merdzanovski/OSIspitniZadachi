#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <string.h>
#include <ctype.h>

char mem[6*1024]; // 6KB
char dop[4*1024]; // 4KB
int w, flag; 

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
    printk("<1> Zdravo, ninjir\n");
    w = 0;
    flag = 0; // koristime mem osnovnata
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
    int z;
    if (flag == 0) {
        if (w >= count) {
            z = count;
        } else {
            z = w;
        }
        copy_to_user(buff, (mem + w) - z, z);
        w-=z;
    } else {
        if (w >= count) {
            z = count;
            copy_to_user(buff,(dop + w) - z, z);
            w -= z;
        } else {
            copy_to_user(buff, dop, w);
            z = count - w;
            w = 6*1024;
            copy_to_user(buff, mem + w - z, z);
            w -= z;
            flag = 0;
        }
    }
}

ssize_t my_write(struct file *fp, const char* buff, size_t count, loff_t *offp) {
    if (flag == 0) {
        if ( (6*1024 - w) >= count) {
            int z = count;
            copy_from_user(mem + w, buff, z);
            w += count;
        } else {
            int z = 6*1024 - w;

            if (z + 4*1024 < count) {
                return 0; // ako ja nadminuva dopolnitelnata memorija
            }

            copy_from_user(mem + w, buff, z);
            flag = 1;
            copy_from_user(dop, buff, count-z);
            w = count - z;
        }
    } else {
        if(4*1024 - w >= count) {
            copy_from_user(dop + w, buff, count);
            w += count;
        } else {
            return 0;
        }
    }
}