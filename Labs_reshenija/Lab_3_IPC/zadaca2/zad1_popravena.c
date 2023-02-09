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

/* 1. Да се напише С програма која работи со процеси и меѓупроцесна комуникација. Главниот процес, како
аргументи од командна линија, добива наредба со аргументи која треба да ја изврши. Потоа, преку
тастатура се внесува колку пати треба да се изврши соодветната наредба Z. Главниот процес креира Z деца
процеси колку што треба да се изврши наредбата, притоа секој еден од деца процесите ја извршува
наредбата еднаш. Иако деца процесите се креираат и се извршуваат паралелно, сепак треба да се овозможи
механизам каде деца процесите ќе се чекаат помеѓу себе т.е. ќе се извршуваат сериски. Главниот процес
треба да брои колку време им требало на деца процесите да завршат со извршување. Комуникацијата
помеѓу деца процесите и синхронизацијата за да се постигне сериско извршување да се изведе со помош на
заедничка (shared) меморија.
Пример:
./prva wc -c -l -d */

int main(int argc, char *argv[])
{

    int i, z;
    key_t kluc = 1200;
    int sekundi = 0;
    int cekaj = 0;
    char *mem;

    printf("Vnesi ja vrednosta na z\n");
    char brojce[10];
    fgets(brojce, 10, stdin);
    z = atoi(brojce);

    pid_t deca[z];

    int id;
    id = shmget(kluc, 1, 0x777 | IPC_CREAT); // 0644 za ov 0x777
    if (id == -1)
    {
        printf("neuspesno dobivanje pristap");
    }

    mem = shmat(id, NULL, 0);
    mem[0] = 0;

    for (i = 1; i <= z; i++)
    {
        deca[i - 1] = fork();
        if (deca[i - 1] == 0)
        {
            break;
        }
    }

    if (i <= z)
    {
        // deca
        id = shmget(kluc, 1, 0644);
        if (id == -1)
        {
            printf("neuspesno dobivanje pristap do memorijata");
            return 0;
        }
        mem = shmat(id, NULL, 0);

        while (mem[0] != (i + '0')) {
            sleep(1);
        }
        shmdt(mem);
        execvp(argv[1], &argv[1]);
        printf("Ne se izvrshi naredbata.\n");
    }
    else
    {
        // roditel
        while (cekaj < z)
        {
            cekaj++;
            mem[0] = cekaj + '0';
            while (waitpid(deca[cekaj - 1], NULL, WNOHANG) != deca[cekaj - 1])
            {
                sleep(1);
                sekundi++;
            }
        }
        printf("Na decata im trebashe %d sekundi da zavrshat\n", sekundi);
    }
    return 0;
}