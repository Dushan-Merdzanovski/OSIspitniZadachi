#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* #include <linux/init.h> */
#include <linux/module.h>
#include <linux/kernel.h>

/* Zadaca2) Да се напише драјвер за виртуелен уред кој ќе врши
запишување и читање во меморијата на драјверот
Карактеристики на драјверот:
- Бафер од 80 бајти
- Знаковен уред
- Мајor number = 60
- Minor number = 0
Креирање на уредот и препознавање од системот:
sudo mknod /dev/ured1 c 60 0
sudo chmod 666 /dev/ured1*/

struct file_operations my_fops = {
    read : my_read,
    write : my_write
    /* open : r_init,
    release : r_cleanup */
};

static int r_init(void)
{
    printk("<1>Zdravo\n");
    if (register_chrdev(60, "cprimer1", &my_fops))
    {
        printk("<1>nejke da registrira\n");
    }
    return 0;
}

static void r_cleanup(void)
{
    printk("<1>sajonara\n");
    unregister_chrdev(60, "cprimer1");
    return;
}

char my_data[80];

ssize_t my_read(struct file *filep, char *buff, size_t count, loff_t *offp)
{
    if (copy_to_user(buff, my_data, strlen(my_data)) != 0)
        printk("Kernel -> userspace kopiranjeto padna!\n");
    return strlen(my_data);
}

ssize_t my_write(struct file *filep, const char *buff, size_t count, loff_t *offp)
{
    if (copy_from_user(my_data, buff, count) != 0)
        printk("Userspace -> kernel kopiranjeto padna!\n");
    return count;
}

int main()
{
    int fd = 0, ret = 0, wr = 0;
    char buff[80] = "";
    fd = open("/dev/ured", O_WRONLY);
    printf("fd :%d\n", fd);
    wr = write(fd, "test", 6);
    printf("zapisano test; dolzina %d bytes\n", wr);
    close(fd);
    fd = open("/dev/ured", O_RDONLY);
    ret = read(fd, buff, 10);
    buff[ret] = '\0';
    printf("buff: %s ;length: %d bytes\n", buff, ret);
    close(fd);
}
