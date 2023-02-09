#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <string.h>
#include <ctype.h>

// ZADACHA4 DRAJVERI JANUARI 2022
// do pola vo edna memorija

char mem[1 * 1024]; // 1KB
int w1, w2;
int flag; // 0 - ne moze nitu eden proces, 1- proces1, 2-proces2

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

    w1 = 0;
    w2 = 512;
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
    if (flag == 0)
    {
        return 0;
    }
    else
    {
        if (flag == 1)
        {
            int r;
            if (w1 >= count)
            {
                r = count;
            }
            else
            {
                r = w1;
            }
            copy_to_user(buff, mem, r);
            flag = 0;
            return r;
        }
        else if (flag == 2)
        {
            int r;
            if (w2 - 512 >= count)
            {
                r = count;
            }
            else
            {
                r = w2 - 512;
            }
            copy_to_user(buff, mem + 512, r);
            flag = 0;
            return r;
        }
        else
        {
            flag = 0;
            return 0;
        }
    }
}

ssize_t my_write(struct file *fp, const char *buff, size_t count, loff_t *offp)
{
    if (flag == 0)
    {
        char c;
        copy_from_user(&c, buff, 1);
        if (c == '1')
        {
            flag = 1;
        }
        else if (c == '2')
        {
            flag = 2;
        }
        else
        {
            flag = 0;
        }
        return 0;
    }
    else
    {
        if (flag == 1)
        {
            if (512 - w1 >= count)
            {
                copy_from_user(mem + w1, buff, count);
                flag = 0;
                return count;
            }
            else
            {
                int d1 = 512 - w1;   // pr. 12, tolku moze vo w1
                int d2 = count - d1; // pr. 88, ako saka vkupno 100 da zapishe
                copy_from_user(mem + w1, buff, d1);
                copy_from_user(mem, buff + d1, d2);
                flag = 0;
                return count;
            }
        }
        else if (flag == 2)
        {
            if (1024 - w2 >= count)
            {
                copy_from_user(mem + w2, buff, count);
                flag = 0;
                return count;
            }
            else
            {
                int d1 = 1024 - w2;  // pr. 12, tolku moze vo w1
                int d2 = count - d1; // pr. 88, ako saka vkupno 100 da zapishe
                copy_from_user(mem + w2, buff, d1);
                copy_from_user(mem + 512, buff + d1, d2);
                w2 = 512 + d2;
                flag = 0;
                return count;
            }
        }
    }
}
