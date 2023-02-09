#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* 
Задача 3: Да се напише програма во C која работи со процеси и нитки. Главната програма (родител
процесот) добива низа од наредби кои треба да ги изврши како аргументи од командна линија. 
Родител процесот треба, најпрво, да креира онолку деца процеси колку што има наредби
наведено од командна линија (наредбите се без аргументи). Пота, треба да креира онолку нитки, 
колку што има наредби, така што, секоја нитка ќе чека и ќе брои колку секунди му било потребно
на соодветниот процес да заврши. Тоа значи дека, првата нитка ќе биде задолжена за првата
наредба т.е. за првиот процес, втората за вториот и т.н. Секоја нитка брои колку време се
извршувал нејзиниот процес (наредба) и кога ќе заврши кажува колку вкупно секунди му требало
да заврши, а потоа и самата нитка завршува. Откако ќе завршат сите процеси/нитки, тогаш
главниот процес/нитка печати на екран колку време и требало на секоја наредба да се изврши.

БОНУС: главниот процес/нитка печати на екран колку време и требало на секоја наредба да се
изврши во растечки редослед според времето на завршување, најпрво да се отпечати која
наредба и требало најмалку време да заврши, па потоа следната наредба и т.н.
*/

pid_t deca[10];
int vreme[10];

void *cekaj(void *id)
{
    int i = *(int *)id;

    int sekundi = 0;
    while (1)
    {
        if (waitpid(deca[i], NULL, WNOHANG) == deca[i])
        {
            break; // WHOHANG go glea statusot na ovoj proces, ako ne zavrsilo vrakja 0/-1, ako zavrsil go vrakja pid na deteto togash brakenuba
        }
        sleep(1);
        sekundi++;
    }
    // printf("Na deteto %d mu trebaa %d sekundi da zavrshi\n",i,sekundi);
    vreme[i] = sekundi;
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    int N;
    int i, j;
    int K[10];

    pthread_t nitki[10];

    N = argc - 1;

    for (i = 0; i < N; i++)
    {
        deca[i] = fork();
        if (deca[i] == 0)
            break;
    }

    if (i < N)
    { // nekoe od dete procesi, posho samo roditelot ke stigne do N, site drugi deca zaradi breakot ke prekinat negde pred N
        // sigurno e dete proces

        // argv[i+1] tekovnata programa,t.e. arg od cmdline
        execlp(argv[i + 1], argv[i + 1], NULL); // execl fiksen broj na argumenti, zavrsuva so NULL
        printf("Neuspesen povik na argv[%d]", i + 1);
    }
    else
    {
        // roditel proces
        for (i = 0; i < N; i++)
        {
            K[i] = i;
            pthread_create(nitki[i], NULL, cekaj, (void *)&K[i]);
        }

        for (i = 0; i < N; i++)
        {
            pthread_join(nitki[i], NULL);
        }

        for (i = 0; i < N; i++)
        {
            printf("Na deteto %d mu trebaa %d sekundi da zavrshi\n", i, vreme[i]);
        }

        // sort bonus

        int j;
        for (i = 0; i < N; i++)
        {
            for (j = i + 1; j < N; j++)
            {
                if (vreme[i] > vreme[j])
                {
                    int pom = vreme[i];
                    vreme[i] = vreme[j];
                    vreme[j] = pom;
                    char pom1[30]; // placeholder string za iminjata na datotekite/naredbite
                    strcpy(pom1,argv[i+1]); // sekad i+1 i j+1
                    strcpy(argv[i+1],argv[j+1]);
                    strcpy(argv[j+1],pom1);
                }
            }
        }

        for (i = 0; i < N; i++)
        {
            printf("Na naredbata %s i trebaa %d sekundi da zavrshi\n", argv[i+1], vreme[i]);
        }
    }

    return 0;
}