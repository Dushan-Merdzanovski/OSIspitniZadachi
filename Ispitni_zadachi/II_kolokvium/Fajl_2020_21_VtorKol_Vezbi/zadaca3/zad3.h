// driver.h
/*
 * my device header file
 */
#ifndef _MY_DEVICE_H
#define _MY_DEVICE_H
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <asm/segment.h>
#include <asm/uaccess.h>

/* Zadaca3) Да се напише Модул за Линукс ОС за запишување на податоци. Модулот работи со меморија од 512
бајти, притоа не дозволува да се чита од меморијата додека истата не е целосно пополнета и
обратно. Иницијално, при вклучување на модулот, меморијата е празна. Додека меморијата не се
пополни целосно, модулот дозволува само запишување во меморијата. Откако меморијата ќе се
пополни целосно, модулот дозволува само читање од меморијата, притоа, читањето го прави од
десно на лево. Доколку се побараат 10 бајти да бидат прочитани, тие ќе бидат последните 10 бајти
од меморијата. На следното читање, ќе се вратат предпоследните count бајти и т.н. се додека не се
прочита целата меморија до почеток. Потоа, системот повторно дозволува само запишување во
меморијата до нејзино целосно исполнување. */

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

int my_open(struct inode *inode, struct file *filep)
{
    printk("<1> Sega sum vo OPEN\n");
    return 0;
}

int my_release(struct inode *inode, struct file *filep)
{
    printk("<1> Sega sum vo RELEASE\n");
    return 0;
}

ssize_t my_read(struct file *filep, char *buff, size_t count, loff_t *offp)
{
    if (locked == 1)
    {
        if ((512 - r) > count)
        {
            copy_to_user(buff, memorija + 512 - r - count, count);
            r += count;
            return count;
        }
        else
        {
            int k = r;
            copy_to_user(buff, memorija, r);
            w = 0;
            locked = 0;
            return k;
        }
    }
    else
    {
        return 0;
    }
}

ssize_t my_write(struct file *filep, const char *buff, size_t count, loff_t *offp)
{
    if (locked == 0)
    {
        if (w + count < 512)
        {
            copy_from_user(memorija + w, buff, count);
            w += count;
            return count;
        }
        else
        {
            int k = 512 - w;
            copy_from_user(memorija + w, buff, k);
            w = 512;
            r = 0;
            locked = 1;
            return k;
        }
    }
    else
    {
        return 0;
    }
}
#endif