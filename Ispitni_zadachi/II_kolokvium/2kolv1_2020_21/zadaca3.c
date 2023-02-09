#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <string.h>
#include <ctype.h>

// ZADACHA3 DRAJVERI 2kol verzija 1 2020/21

/* Дешифрирање на текст:
Запишување на точна шифра во драјверот + читање од драјверот
Менување на содржина на текст:
Запишување на точна шифра во драјверот + запишување во драјверот.  */

char mem[512];
char sifra[10];
int r;
int encrypted; // 0 - ne e sifriran tekstot, 1 - sifriran e tekstot, 2 - ushte nema zapishano shifra

static int r_init(void);
static void r_cleanup(void);
module_init(r_init);
module_exit(r_cleanup);

int my_open(struct inode *inode, struct file *filep);
int my_release(struct inode *inode, struct file *filep);
ssize_t my_read(struct file *filep, char *buff, size_t count, loff_t *offp);
ssize_t my_write(struct file *filep, const char *buff, size_t count, loff_t *offp);
void shifriraj(char *shifra, char *tekst, char *shifriran);
struct file_operations my_fops = {
    open : my_open,
    read : my_read,
    write : my_write,
    release : my_release,
};

static int r_init(void)
{
    printk("<1> Zdravo, ninji\n");

    encrypted = 0;
    r = 0;
    strcpy(sifra, "");

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
    if (encrypted == 0)
    {
        int d;
        if (512 - r >= count)
        {
            d = count;
        }
        else
        {
            d = 512 - r;
        }
        copy_to_user(buff, mem + r, d);
        shifriraj(sifra, mem, mem);
        return d;
    }
    else
    { // ako encrypted == 1 || 2 <- use nema sifra zapishano
        return 0;
    }
}

ssize_t my_write(struct file *fp, const char *buff, size_t count, loff_t *offp)
{
    if (encrypted == 2)
    { // prvo zapishuvanje
        copy_from_user(sifra, buff, 9);
        encrypted = 0;
        return 0;
    }
    else if (encrypted == 1)
    {
        char code[10];
        copy_from_user(code, buff, 9);
        if (strcmp(sifra, code) == 0)
        {
            deshifriraj(sifra, mem, mem);
            encrypted = 0;
            return 0;
        }
    }
    else if (encrypted == 0)
    {
        copy_from_user(mem, buff, count);
        shifriraj(sifra, mem, mem);
        encrypted = 1;
        return count;
    }
    return 0;
}

void shifriraj(char *shifra, char *tekst, char *shifriran)
{
    int i;
    int pom;
    int j = strlen(shifra);
    for (i = 0; i < strlen(tekst); i++)
    {
        pom = ((int)tekst[i]) + ((int)shifra[j]); // za strlen potrebno e da se vkluci <string.h>
        if (pom > 255)
        {
            pom = pom - 255;
        }
        shifriran[i] = pom;
        j--;
        if (j < 0)
        {
            j = strlen(shifra);
        }
    }
    shifriran[i] = 0;
}

void deshifriraj(char *shifra, char *tekst, char *shifriran)
{
    int i;
    int pom;
    int j = strlen(shifra);
    for (i = 0; i < strlen(tekst); i++)
    {
        pom = ((int)tekst[i]) - ((int)shifra[j]); // za strlen potrebno e da se vkluci <string.h>
        if (pom > 255)
        {
            pom = pom - 255;
        }
        shifriran[i] = pom;
        j--;
        if (j < 0)
        {
            j = strlen(shifra);
        }
    }
    shifriran[i] = 0;
}