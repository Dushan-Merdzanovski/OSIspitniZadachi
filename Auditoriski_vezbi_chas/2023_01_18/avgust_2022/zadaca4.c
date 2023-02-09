#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <string.h>
#include <ctype.h>

// ZADACHA4 DRAJVERI AVGUST 2022
// 3 memorii po 512B

char mem1[512];
char mem2[512];
char mem3[512];
int w1, w2, w3;
int flag; // 0 - ne moze nitu eden proces, 1- proces1, 2-proces2, 3-proces3

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

    w1 = w2 = w3 = 0;
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
    if (flag == 0 || flag == 1)
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
        copy_to_user(buff, mem1 + w1 - r, r);
        flag = 0;
        return r;
    }
    else if (flag == 2)
    {
        int r;
        if (w2 >= count)
        {
            r = count;
        }
        else
        {
            r = w2;
        }
        copy_to_user(buff, mem2 + w2 - r, r);
        flag = 0;
        return r;
    }
    else if (flag == 3)
    {
        int r;
        if (w3 >= count)
        {
            r = count;
        }
        else
        {
            r = w3;
        }
        copy_to_user(buff, mem3 + w3 - r, r);
        flag = 0;
        return r;
    }
}

ssize_t my_write(struct file *fp, const char *buff, size_t count, loff_t *offp)
{
    if (flag == 0)
    {
        char c;
        copy_from_user(c, buff, 1);
        if (c == '1')
        {
            flag = 1;
            return 0;
        }
        else if (c == '2')
        {
            flag = 2;
            return 0;
        }
        else if (c == '3')
        {
            flag = 3;
            return 0;
        }
        else
        { // treba da zapisheme vo prvata memorija
            mem1[w1] = c;
            w1++;
            int w;
            if (512 - w1 >= count - 1)
            { // count - 1 posho sme zapishale eden vishe
                w = count - 1;
            }
            else
            {
                w = 512 - w1;
            }
            copy_from_user(mem1 + w1, buff + 1, w);
            w1 += w;
            flag = 0;
            return w + 1;
        }
    }
    else if (flag == 1)
    {
        int w;
        if (512 - w1 >= count)
        { // count-1 posho sme zapishale eden vishe
            w = count;
        }
        else
        {
            w = 512 - w1;
        }
        copy_from_user(mem1 + w1, buff, w);
        flag = 0;
        w1 += w;
        return w + 1;
    }
    else if (flag == 2)
    {
        int w;
        if (512 - w2 >= count)
        {
            w = count;
        }
        else
        {
            w = 512 - w2;
        }
        copy_from_user(mem2 + w2, buff, w);
        flag = 0;
        w2 += w;
        return w + 1;
    }
    else if (flag == 3)
    {
        int w;
        if (512 - w3 >= count)
        {
            w = count;
        }
        else
        {
            w = 512 - w3;
        }
        copy_from_user(mem3 + w3, buff, w);
        flag = 0;
        w3 += w;
        return w + 1;
    }
    return 0;
}
