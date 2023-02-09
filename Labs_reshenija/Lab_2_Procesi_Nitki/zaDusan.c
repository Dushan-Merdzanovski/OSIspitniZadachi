#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define MAX 1000

int K;
int N;
int niza[MAX];
int proces1_id;
int proces2_id;
char tmp[5];
int dali_najdov1 = 0;
int dali_najdov2 = 0;

void *prebaruvaj(void *t)
{
    int k;
    int indeks;
    long tid = (long)t;
    srand(time(NULL));
    for (k = 0; k < N; k++)
    {
        indeks = rand() % N;
        printf("Thread %d generated the index %d!\n", tid, indeks);
        if ((niza[indeks] == K) && (getpid() == proces1_id))
        {
            printf("Jas sum nitka %d od procesot %d i go najdov elementot %d na pozicija %d!\n", t, proces1_id, K, indeks);
            dali_najdov1 = 1;
            execlp("kill", "kill", "-9", "proces1_id", NULL);
        }
        if ((niza[indeks] == K) && (getpid() == proces2_id))
        {
            printf("Jas sum nitka %d od procesot %d i go najdov elementot %d na pozicija %d!\n", t, proces2_id, K, indeks);
            dali_najdov2 = 1;
            execlp("kill", "kill", "-9", "proces2_id", NULL);
        }
    }
    pthread_exit((void *)t);
}

int main(int argc, char *argv[])
{
    N = atoi(argv[1]);
    K = atoi(argv[2]);
    pid_t dete;
    char c;
    int broj = 0;
    int i = 0;
    proces1_id = getpid();
    dete = fork();
    if (dete == 0)
    {
        proces2_id = getpid();
    }
    FILE *dat;
    if ((dat = fopen("lab3.txt", "r")) == NULL)
    {
        fprintf(stderr, "Ne mozam da ja otvoram datotekata dat.txt\n");
        return -1;
    }
    while ((c = fgetc(dat)) != EOF)
    {
        if (c == ' ')
        {
            niza[i++] = broj;
            broj = 0;
        }
        else
        {
            broj = broj * 10 + c;
        }
    }
    niza[i] = broj;
    pthread_t threads[5];
    int rc = 0;
    void *status;
    for (int j = 0; j < 5; j++)
    {
        printf("Jas sum procesot %d i ke ja kreiram nitkata %d", getpid(), j);
        rc = pthread_create(&threads[j], NULL, prebaruvaj, (void *)&j);
        if (rc)
        {
            printf("Error, return code from pthreda_create is %d!\n", rc);
            return -1;
        }
    }
    for (int j = 0; j < 5; j++)
    {
        printf("Jas sum procesot %d i ja cekam nitkata %d", getpid(), j);
        rc = pthread_join(threads[j], &status);
        if (rc)
        {
            printf("Error, return code from pthread_join is %d", rc);
            return -1;
        }
    }
    if ((getpid() == proces1_id) && (dali_najdov1 == 0))
    {
        printf("Main thread from process %d completed. without finding the number. Exiting!\n", getpid());
    }
    if ((getpid() == proces2_id) && (dali_najdov2 == 0))
    {
        printf("Main thread from process %d completed. without finding the number. Exiting!\n", getpid());
    }
    printf("Main thread from process %d completed. Exiting!\n", getpid());
    pthread_exit(NULL);
}
