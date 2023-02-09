#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* #include <linux/init.h> */
#include <linux/module.h>
#include <linux/kernel.h>

// prez AV_10: Drajveri
/* Zadaca1) Да се креира виртуелен знаковен уред до кој би праќале податоци.
Потоа да се креира драјвер кој ќе може да запише и да прочита од овој
уред. */

struct file_operations hello_fops = {
    read : hello_read,
    write : hello_write,
    open : hello_open,
    release : hello_release
};

static int hello_init(void)
{
    int ret;
    printk("Hello example Init ");
    ret = register_chrdev(60, "hello1", &hello_fops);
    if (ret < 0)
    {
        printk("Error egistering hello device\n");
        goto hello_fail1;
    }
    printk("Hello: registered module successfully !\n");
    /* Init processing here... */
    return 0;
hello_fail1:
    return ret;
}

static void hello_exit(void)
{
    unregister_chrdev(60, "hello1");
    printk("Hello Example Exit\n");
}

static int hello_open(struct inode *inode, struct file *file)
{
    printk("hello_open: successful\n");
    return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
    printk("hello_release: successful\n");
    return 0;
}

static ssize_t hello_read(struct file *file, char *buf, size_t count, loff_t *ptr)
{
    printk("hello_read: returning zero bytes\n");
    return 0;
}

static ssize_t hello_write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
    printk("hello_write: accepting zero bytes\n");
    return 0;
}