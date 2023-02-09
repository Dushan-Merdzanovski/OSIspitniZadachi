#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/module.h>
#include <linux/kernel.h>
/* #include <linux/init.h>*/
#include <zad2.h>

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
// driver.c */

MODULE_AUTHOR("flaop");
MODULE_DESCRIPTION("flaop driver");
char orig[10240], ogledalo[10240];
int use;
char *pocetok, *kraj;
static int r_init(void);
static void r_cleanup(void);
module_init(r_init);
module_exit(r_cleanup);

static int r_init(void)
{
    use = 0;
    pocetok = orig;
    kraj = ogledalo + 10240 - 1;
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