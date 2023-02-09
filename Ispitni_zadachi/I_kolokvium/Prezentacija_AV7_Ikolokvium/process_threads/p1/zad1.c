#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
Да се напише програма во C која работи со процеси и нитки. Главната програма
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
на случајни броеви се прави со помош на функцијата rand( ).
БОНУС: Проверката колку елементи од низата ја имаат променето својата
вредност да ја прави родител процесот.
*/

int N;
int arr[100];

typedef struct
{
    int vrednost;
    int k;
} p;

void * promeni(void* id) {

    p j = *(p*) id;
    int i, l;
    srand(time(NULL));
    for (i = 0; i < j.k; i++) {
        l = rand() % 100;
        arr[l] += j.vrednost;
    }

    pthread_exit(NULL);
}

/* void *zgolemi(void *id)
{
    int k = *(int *)id;

    for (int i = 0; i < k; i++)
    {
        int p = rand() % 100;
        arr[p]++;
    }
    pthread_exit(NULL);
}

void *namali(void *id)
{
    int k = *(int *)id;

    for (int i = 0; i < k; i++)
    {
        int p = rand() % 100;
        arr[p]--;
    }
    pthread_exit(NULL);
} */

int main(int argc, char *argv[])
{
    printf("Vnesi go brojot na nitki\n");
    scanf("%d", &N);

    pthread_t threads[100];
    pid_t dete;
    dete = fork();
    p id[N];

    if (dete == 0)
    {
        for (int i = 0; i < 100; i++)
        {
            arr[i] = 0;
        }

        for (int i = 0; i < N; i++)
        {
            id[i].k = rand() % 20;
            if (i < N / 2)
                id[i].vrednost = 1;
            else
                id[i].vrednost = -1;

            pthread_create(&threads[i],NULL,promeni,(void*)&id[i]);
        }

        for (int i = 0; i < N; i++)
        {
            pthread_join(threads[i], NULL);
        }

        int count = 0;
        for (int i = 0; i < 100; i++)
        {
            if (arr[i] != 0)
            {
                count++;
            }
        }
        printf("Br:%d elementi ja imaat promeneto svojata vrednost!\n", count);
    }
    else
    {
        wait(NULL);
        printf("Zavrshi dete procesot\n");
    }

    return 0;
}