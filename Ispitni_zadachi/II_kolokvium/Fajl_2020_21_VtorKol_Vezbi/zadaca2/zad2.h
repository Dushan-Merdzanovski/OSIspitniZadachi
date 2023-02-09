// driver.h
/*
 * my device header file
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#ifndef _MY_DEVICE_H
#define _MY_DEVICE_H
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <asm/segment.h>
#include <asm/uaccess.h>

/* 2. Да се напише Модул за Линукс ОС за запишување на податоци. Модулот има првична меморија од
1024KB и огледална (mirror) меморија од исто толку KB. Иницијално меморијата е празна. Кога
првичната меморија не е полна, се запишува во таа меморија сите податоци што се запишуваат во
модулот, а се прави дополнителна копија во огледалната меморија (од крајот кон почетокот). Во
моментот кога ќе се наполни оригиналната меморија, огледалната меморија служи како дополнителна
меморија, така што дополнителните податоци се запишуваат таму почнувајќи од почеток. Кога ќе се
прочита од модулот, доколку огледалната меморија има копија од првичната меморија се прави
проверка дали тоа што се чита е исто и во првичната и во огледалната ( Double Check). Доколку е исто,
на корисникот му се враќа информација дека меморијата е Double Checked. Доколку не е исто, на
корисникот се враќа информација дека имало Double Check ама истиот не е успешно извршен. Како трет
случај се зема кога огледалната меморија се користи како дополнителна меморија, тогаш се враќа
информација на корисникот дека не е возможно да се направи Double Check.
// zad2.h */

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
    if (use == 0)
    {
        int kk = pocetok - orig >= count ? count : pocetok - orig;
        int flag = 1;
        char *p, *k;
        p = pocetok;
        k = kraj - kk; // why -kk?
        for (int i = 0; i < kk; i++)
        {
            if (*p != *k)
            {
                flag = 0;
                break;
            }
            p--;
            k++;
        }
        copy_to_user(buff, (flag == 1) ? "2" : "1", 1);
        copy_to_user(buff + 1, pocetok - kk, kk);
        return kk;
    }
    else
    {
        if (pocetok > ogledalo)
        {
            if (pocetok - ogledalo > count)
            {
                copy_to_user(buff, "0", 1);
                copy_to_user(buff + 1, pocetok - count, count);
                return count;
            }
            else
            {
                int k = pocetok - ogledalo;
                copy_to_user(buff, "0", 1);
                copy_to_user(buff + 1, ogledalo, k);
                copy_to_user(buff + 1 + k, orig + 10240 - (count - k), count - k);
                pocetok = orig + 102040 - (count - k);
                return count;
            }
        }
        else
        {
            if (pocetok - orig > count)
            {
                copy_to_user(buff, "0", 1);
                copy_to_user(buff + 1, pocetok - count, count);
                return count;
            }
            else
            {
                int k = pocetok - orig;
                copy_to_user(buff, "0", 1);
                copy_to_user(buff + 1, orig, k);
                use = 0;
                return k;
            }
        }
    }
}

ssize_t my_write(struct file *filep, const char *buff, size_t count, loff_t *offp)
{
    if (use == 0)
    {
        if (pocetok + count < orig + 10240)
        {
            copy_from_user(pocetok, buff, count); // (to, from, number)
            for (int i = 0; i < count; i++)
            {
                *kraj = *pocetok;
                kraj--;
                pocetok++;
            }
            return count;
        }
        else
        {
            int k = orig + 10240 - pocetok;
            copy_from_user(pocetok, buff, k); // (to, from, number)
            copy_from_user(ogledalo, buff + k, count - k);
            pocetok = ogledalo + count - k;
            use = 1;
        }
    }
    else
    {
        if (pocetok + count < ogledalo + 10240)
        {
            copy_from_user(pocetok, buff, count);
            pocetok += count;
            return count;
        }
        else
        {
            int k = ogledalo + 10240 - pocetok;
            copy_from_user(pocetok, buff, k);
            pocetok += k;
            return k;
        }
    }
}
#endif