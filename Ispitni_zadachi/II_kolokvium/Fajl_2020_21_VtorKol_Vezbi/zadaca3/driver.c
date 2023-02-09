

// driver.c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/module.h>
#include <linux/kernel.h>
/* #include <linux/init.h> */
#include <zad3.h>

/* Zadaca3) Да се напише Модул за Линукс ОС за запишување на податоци. Модулот работи со меморија од 512
бајти, притоа не дозволува да се чита од меморијата додека истата не е целосно пополнета и
обратно. Иницијално, при вклучување на модулот, меморијата е празна. Додека меморијата не се
пополни целосно, модулот дозволува само запишување во меморијата. Откако меморијата ќе се
пополни целосно, модулот дозволува само читање од меморијата, притоа, читањето го прави од
десно на лево. Доколку се побараат 10 бајти да бидат прочитани, тие ќе бидат последните 10 бајти
од меморијата. На следното читање, ќе се вратат предпоследните count бајти и т.н. се додека не се
прочита целата меморија до почеток. Потоа, системот повторно дозволува само запишување во
меморијата до нејзино целосно исполнување. */

MODULE_AUTHOR("flaop");
MODULE_DESCRIPTION("flaop driver");
char memorija[512];
int r, w;
int locked; // 0 - zapisuvame, 1 - citame
static int r_init(void);
static void r_cleanup(void);
module_init(r_init);
module_exit(r_cleanup);

static int r_init(void)
{
    r = 0;
    w = 0;
    locked = 0;
    printk("<1>Zdravo ninji\n");
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