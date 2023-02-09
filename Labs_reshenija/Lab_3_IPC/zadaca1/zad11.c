#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

/* Задача 1. Да се напише C програма која ќе креира три типови (типот се праќа како прв
аргумент од командна линија) на процеси кои ќе комуницираат помеѓу себе преку
заедничка „shared“ меморија. Како втор аргумент се праќа клучот преку кој ќе
комуницираат процесите од заедничката меморија. Првиот тип на процес чита од
тастатура одредена порака и ја запишува во меморијата и сигнализира на третиот тип на
процес да прочита од меморијата и заспива одреден број на секунди (случајно се одбира
од 1 до 10 со функцијата rand()%10+1). Третиот тип на процес доколку има што да
прочита од меморијата, го чита и печати на екран и заспива исто како и првиот тип на
процес. Вториот тип на процес на секои 5 секунди ја брише пораката од заедничката
меморија со пополнување на нули. */

int main(int argc, char *argv[])
{
    int k = atoi(argv[2]); // 1234
    key_t kluc = k;
    srand(time);

    if (!strcmp(argv[1], "prv"))
    {
        char *poraka;
        printf("Vnesete poraka\n");
        scanf("%s", poraka);
        int id;
        id = shmget(kluc, 1024, 0666 | IPC_CREAT);
        if (id < 0)
        { // == -1
            printf("Neuspeshno dobivanje pristap do memorijata.  \n");
            return 0;
        }
        char *mem;
        mem = shmat(id, mem, 0);

        if (mem == NULL)
        {
            printf("Neuspesno prikacuvanje na memorijata\n");
            return 0;
        }

        while (1)
        {
            if (mem[0] != 'l')
            {
                mem[0] = 'l';
                strcat(mem, poraka);
                mem[0] = 'u';
                sleep(rand() % 10 + 1);
            }
            else
            {
                sleep(1);
            }
        }
        shmdt(mem); // detatch
    }
    else if (!strcmp(argv[1], "vtor"))
    {
        // sleep 5 na pochetok
        int id;
        id = shmget(kluc, 1024, 0666 | IPC_CREAT);
        if (id < 0)
        { // == -1
            printf("Neuspeshno dobivanje pristap do memorijata.  \n");
            return 0;
        }
        char *mem;
        mem = shmat(id, mem, 0);

        if (mem == NULL)
        {
            printf("Neuspesno prikacuvanje na memorijata  KAJ TIP 1\n");
            return 0;
        }

        while (1)
        {
            if (mem[0] != 'l')
            {
                mem[0] = 'l';
                int i = 1;
                while (mem[i] != '\0')
                {
                    mem[i] = '0';
                    i++;
                }
                mem[0] = 'u';
                sleep(5);
            }
            else
            {
                sleep(1);
            }
        }
        shmdt(mem); // detatch
        shmctl(id, IPC_RMID, 0);
    }
    else if (!strcmp(argv[1], "tret"))
    {
        // napraj mu sleep 5, za da mozhe da se vnese porakata
        // chuvaj ushte eden bajt, t.e. vtoriot bajt od shmemory neka bide 0 ili 1, 
        // za dali ima zapishana poraka ili nema. Ako e 1, neka ja isprinta tretiov, ako e 0, neka sleepne random sekundi
        int id;
        id = shmget(kluc, 1024, 0666 | IPC_CREAT);
        if (id < 0)
        { // == -1
            printf("Neuspeshno dobivanje pristap do memorijata.  \n");
            return 0;
        }
        char *mem;
        mem = shmat(id, mem, 0);

        if (mem == NULL)
        {
            printf("Neuspesno prikacuvanje na memorijata KAJ TIP 3\n");
            return 0;
        }

        while (1)
        {
            if (mem[0] != 'l')
            {
                mem[0] = 'l';
                if (mem[1] != '0')
                {
                    char zbor[20];
                    int i = 0;
                    for (i = 0; i < strlen(mem); i++)
                    {
                        zbor[i] = mem[i + 1];
                    }
                    zbor[i] = '\0';
                    printf("Porakata od tip3 : %s\n",zbor);
                    mem[0] = 'u';
                    sleep(rand() % 10 + 1);
                }
                else
                {
                    mem[0] = 'u';
                    sleep(rand() % 10 + 1);
                }
            }
            else
            {
                sleep(1);
            }
        }
        shmdt(mem); // detatch
    }

    return 0;
}