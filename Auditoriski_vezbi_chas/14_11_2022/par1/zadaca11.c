#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*Задача1: Да се напише програма во C која работи со процеси и нитки. Главната програма
(родител процесот) треба да креира дете процес, на кого ќе му прати низа од 100
цели броеви. Дете процесот најпрво треба да ја пополни низата од 100 цели
броеви со нули. Потоа, дете процесот треба да креира N нитки (N се внесува од
тастатура во родител процесот), притоа на секоја нитка дете процесот и испраќа
(како аргумент) случаен позитивен цел број „К“ (најмногу 500). Секоја нитка
прави „К“ промени во низата и потоа завршува со работа. Секоја една промена
во низата значи случајно одбирање на еден елемент од низата и менување на
неговата вредност. Првата половина од нитките ја менуваат вредноста на
елементот со зголемување на неговата вредност за 1, додека пак втората
половина на нитките ја намалуваат вредноста на елементот за 1. Откако ќе
завршат со работа сите нитки, главната нитка (дете процесот) печати на екран
колку елементи од низата ја имаат променето својата вредност (т.е. не се повеќе
нула). Родител процесот завршува откако дете процесот ќе заврши. Генерирањето
на случајни броеви се прави со помош на функцијата rand().*/

int N;
int niza[100];

typedef struct
{
    int i;
    int k;
} p;


// zgolemi i namali se starite funkcii, promeni e novata!!!
/* void *zgolemi(void *id)
{
    int k = *(int *)id;
    int i, j; // j e sluchaen broj
    for (i = 0; i < k; i++)
    {
        j = rand() % 100; // goki so % go napisha ova, se mislev za so * ama rand() vo C generira integer, ne decimalen broj
        niza[j]++;
    }
    pthread_exit(NULL);
} */

/* void *namali(void *id)
{
    p z = *(p *)id;
    int i, j; // j e sluchaen broj
    for (i = 0; i < .k; i++)
    {
        j = rand() % 100; // goki so % go napisha ova
        niza[j] = z.i;
    }
    pthread_exit(NULL);
} */

void *promeni(void *id)
{

    p z = *(p *)id;
    int i, j; // j e sluchaen broj

    for (i = 0; i < z.k; i++)
    {
        j = rand() % 100; // goki so % go napisha ova
        niza[j] += z.i;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t nitki[100];
    pid_t dete;
    p id[100];
    printf("Vnesi go brojot na nitki");
    scanf("%d", &N);

    dete = fork();
    if (dete == 0)
    {
        // dete proces

        for (int i = 0; i < 100; i++)
        {
            niza[i] = 0;
        }

        for (int i = 0; i < N; i++)
        {
            id[i].k = rand() * 501; // ili so % ?
            // kako da go rehsime probleemot so id-s, isti ke dobivaat u princip sea ke go reshi
            if (i < N / 2)
                id[i].i = 1;
            else
                id[i].i = -1;

            pthread_create(&nitki[i], NULL, promeni, (void *)&id[i]);
        }
        for (int i = 0; i < N; i++)
        {
            pthread_join(nitki[i], NULL);
        }
        int kolku = 0;
        for (int i = 0; i < 100; i++)
        {
            if (niza[i] != 0)
                kolku++;
        }
        printf("Promeneti se %d elementi.", kolku);
    }
    else
    {
        wait(NULL);
        printf("Zavrshi dete procesot");
    }

    return 0;
}