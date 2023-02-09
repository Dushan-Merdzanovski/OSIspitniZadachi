#ifndef _MY_DEVICE_H
#define _MY_DEVICE_H
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <asm/segment.h>
#include <asm/uaccess.h>

// 2014_2015_Operativni_sistemi_II_Kolokvium

/* 3. Да се напише драјвер во C програмскиот јазик кој што ќе овозможува контролирано читање на блокови
од меморијата на даден уред. Меморијата на уредот е 4KB, притоа предефинирано се читаат по 64 бајти
(блок) од меморија. На секое последователно читање на бајти од меморијата покажувачот се поместува
во десно. Кога ќе стигне до крајот на меморијата, се рестартира покажувачот и почнува од почеток.
Доколку се запише нешто во драјверот, тогаш се менува големината на блоковите што се читаат од
меморија. Доколку се смени големината на блокот со вредност која што не е делива со 64, тогаш се чита
следната големина најблиску до број делив со 64 (пример: за блок од 130 бајти се читаат 192 бајти
меморија). Доколку се внесе вредност поголема од 4K, тогаш најмногу се чита 4К. */

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

ssize_t my_read(struct file *filep, char *buff, size_t count, loff_t *offp) {
    if (read + size <= 4096) {
        copy_to_user(buff, mem + read, size);
        read += size;
        return size;
    }
    else {
        copy_to_user(buff, mem + read, 4096 - read);
        read = 0;
        return 4096 - read;
    }
}

ssize_t my_write(struct file *filep, const char *buff, size_t count, loff_t *offp) {
    char newSize[30];
    int ns;
    copy_from_user(newSize, buff, count);
    ns = atoi(newSize);
    /* if (ns == 0) {
        ns = 64;
    } */
    if (ns > 4096) {
        ns = 4096
    }

    if (ns % 64 > 0) {
        size = (ns / 64 + 1) * 64;
    }
    else {
        size = ns;
    }
    return count;
}
#endif