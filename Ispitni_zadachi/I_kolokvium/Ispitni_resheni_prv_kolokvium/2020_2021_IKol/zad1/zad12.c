#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*1. Да се напише програма во C која работи со процеси и нитки. Главната програма (родител процесот)
пополнува низа од 1000 броеви на случаен начин со помош на rand() функцијата. Потоа, креира два
деца процеси, така што, двата деца процеси вршат пребарување на бројот 0 во низата од 1000 броеви.
Првото дете процес, пребарувањето го прави со помош на 10 деца процеси, додека пак второто дете,
пребарувањето го прави со 10 нитки. Секоја нитка/дете процес добива дел од низата што треба да го
пребара бројот 0 и печати на екран колку пати е пронајден бројот кај соодветната нитка/дете процес.
Родител процесот чека да завршат двете деца процеси и на екран печати кое од двете завршило прво.
Доколку прво заврши дете процесот кое пребарувањето го прави со помош на деца процеси, тогаш на
екран се печати +pobrzo zavrshi prebaruvanjeto so deca procesi“, инаку печати +pobrzo zavrsi prebaruvanjeto
so nitki“.
БОНУС: Да се имплементира кодот така што двете деца процеси печатат само по еднаш колку вкупно е
пронајдена 0. Кај првото дете процес, комуникацијата со децата процеси кои пребаруваат да се прави со
помош на датотека со име +communicate.txt“*/
#define N 1000
int niza[N];

void *izbroi(void *j)
{
    int i = *((int *)j);
    int count = 0;
    for (int p = i * 100; p < i * 100 + 100; p++)
    {
        if (niza[p] == 0)
        {
            count++;
        }
    }
    printf("Brojot 0 e najden %d pati vo %d NITKA na dete1\n", count, i);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pid_t prvodete;

    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        niza[i] = rand() % 10;
    }

    prvodete = fork();

    if (prvodete == 0)
    { // prvo dete so procesi
        pid_t child[10];
        int j;
        for (j = 0; j < 10; j++)
        {
            child[j] = fork();
            if (child[j] == 0)
                break;
        }

        if (j < 10)
        { // children na dete0
            int p = 0;
            int count = 0;
            for (p = j * 100; p < j * 100 + 100; p++)
            {
                if (niza[p] == 0)
                {
                    count++;
                }
            }
            printf("Brojot 0 e najden %d pati vo %d CHILD na dete0\n", count, j);
        }
    } else
    {
        pid_t vtorodete = fork();

        if (vtorodete == 0) {
            pthread_t threads[10];
            for (int k = 0; k < 10; k++)
            {
                pthread_create(&threads[k], NULL, izbroi, (void *)&k);
            }

            for (int k = 0; k < 10; k++)
            {
                pthread_join(threads[k],NULL);
            }
            printf("Ja sum dete1 gi dochekav nitkite da zavrshat.\n");
        } else {
            pid_t check1 = wait(NULL);
            wait(NULL);

            if(check1 == prvodete) 
                printf("Deteto 0 zavrshilo prvo.\n");
            else 
                printf("Deteto 1 zavrshilo prvo.\n");
        }   
    }

    return 0;
}