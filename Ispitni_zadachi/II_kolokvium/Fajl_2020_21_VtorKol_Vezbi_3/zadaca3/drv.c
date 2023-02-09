#include <linux/module.h>
#include <linux/init.h>
#include "zad3.h"

/* 3. Да се напише драјвер во C програмскиот јазик кој што ќе овозможува контролирано читање на блокови
од меморијата на даден уред. Меморијата на уредот е 4KB, притоа предефинирано се читаат по 64 бајти
(блок) од меморија. На секое последователно читање на бајти од меморијата покажувачот се поместува
во десно. Кога ќе стигне до крајот на меморијата, се рестартира покажувачот и почнува од почеток.
Доколку се запише нешто во драјверот, тогаш се менува големината на блоковите што се читаат од
меморија. Доколку се смени големината на блокот со вредност која што не е делива со 64, тогаш се чита
следната големина најблиску до број делив со 64 (пример: за блок од 130 бајти се читаат 192 бајти
меморија). Доколку се внесе вредност поголема од 4K, тогаш најмногу се чита 4К. */

MODULE_AUTHOR("flaop");
MODULE_DESCRIPTION("flaop driver");
char mem[4096];
int size;
int read;
static int r_init(void);
static void r_cleanup(void);
module_init(r_init);
module_exit(r_cleanup);

static int r_init(void) {
    size = 64;
    read = 0;
    printk("<1>Zdravo ninji\n");
    if (register_chrdev(60, "cprimer1", &my_fops)) {
        printk("<1>nejke da registrira\n");
    }
    return 0;
}

static void r_cleanup(void) {
    printk("<1>sajonara\n");
    unregister_chrdev(60, "cprimer1");
    return;
}