#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <string.h>
#include <ctype.h>

char *mem[512];
int w, bytes_read, bytes_written;
int flag; // 0 - nishto, 1 - read, 2 - write
int key;  // 0 - nisto, 1-read, 2-write, 3-

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

static int r_init(void)
{
    printk("<1> Zdravo, ninji\n");

    w = bytes_read = bytes_written = 0;
    flag = 0;

    if (register_chrdev(60, "primer1", &my_fops))
    {
        printk("<1> Ne saka da registrira\n");
        return 1;
    }
    return 0;
}

static void r_cleanup(void)
{
    printk("<1>Sayonara\n");
    unregister_chrdev(60, "primer1");
}

ssize_t my_read(struct file *fp, char *buff, size_t count, loff_t *offp)
{
    if (key == 1)
    {
        int r;
        if (w >= count)
        {
            r = count
        }
        else
        {
            r = w;
        }
        copy_to_user(buff, mem, r);
        bytes_read += r;
        /* return r; */
    }
    else if (key == 3)
    {
        return bytes_read;
    }
    else if (key == 4)
    {
        return bytes_written;
    }
    else
    {
        return 0;
    }
}

ssize_t my_write(struct file *fp, const char *buff, size_t count, loff_t *offp)
{
    int skip = 0;
    char c;
    if (key == 0)
    {
        copy_from_user(&c, buff, 1);
        switch (c)
        {
        case '1':
            key = 1;
            break;
        case '2':
            key = 2;
            break;
        case '3':
            key = 3;
            break;
        case '4':
            key = 4;
            break;
        default:
            key = 0;
            break;
        }
        return 0;
    } else if (key == 2) {
        int written;
        if (512 - w >= count) {
            written = count;
        } else {
            written = 512 - w;
        }
        copy_from_user(mem+w, buff, written);
        w += written;
        bytes_written += written;
        /* return written; */
    } else {    
        return 0;
    }
}