/* Zadaca2: Да се напише програма за пребарување на
најголемиот елемент во низа од 1000 
случајно генерирани броеви. Програмата
треба да креира 10 нитки кои што најпрво ќе
генерираат 1000 броеви (секоја по 100). 
Потоа, треба да се креираат нови 10 нитки
кои што ќе ги изминат тие 1000 (секоја
своите 100) и ќе го најдат најголемиот
елемент. На крај, главната програма треба да
го испише најголемиот генериран број.*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#define NULL ((void *)0)

#define NUM_THREADS 10
#define NUM_NUMBERS 100
int max = -2147483647; // najmala mozna vrednost, t.e.  -2147483647
int nizi[NUM_THREADS][NUM_NUMBERS];

pthread_t threadg[NUM_THREADS];
void *generiraj(void *t)
{
    int i;
    long tid = (long)t;
    pthread_t ttid = pthread_self();
    srand(time(NULL));
    printf("Thread %ld start generating\n", tid);
    for (i = 0; i < NUM_NUMBERS; i++)
    {
        nizi[tid][i] = rand() % 100; // niza[tid*100+i]= rand()%100; ova e razlikata so rand();
    }
    pthread_exit((void *)t);
}

void *prebaraj(void *t)
{
    int i, rc = 1, cycles = 0;
    long tid = (long)t;
    void *status;
    printf("Thread %ld start searching\n", tid);
    /*  while(rc){
    rc=pthread_join(threadg[tid],&status);cycles++;
    if(cycles>10) break;
    }
    if(rc){printf("Failed to join %ld\n",tid); pthread_exit((void*) t);}*/
    for (i = 0; i < NUM_NUMBERS; i++)
    {
        printf("\t %d\t", nizi[tid][i]);
        if (nizi[tid][i] > max)
            max = nizi[tid][i];
    }
    pthread_exit((void *)t);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc1, rc2;
    long t;
    void *status;
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: creating thread %ld\n", t);
        rc1 = pthread_create(&threadg[t], NULL, generiraj, (void *)t);
        if (rc1)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc1);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++)
    {
        rc1 = pthread_join(threadg[t], &status);
        if (rc1)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc1);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
    }

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: creating thread %ld \"\n", t);
        rc2 = pthread_create(&threads[t], NULL, prebaraj, (void *)t);
        if (rc2)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc2);
            exit(-1);
        }
    }
    for (t = 0; t < NUM_THREADS; t++)
    {
        rc1 = pthread_join(threads[t], &status);
        if (rc1)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc1);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
    }
    printf("Main: program completed. %d e najgolem. Exiting.\n", max);
    pthread_exit(NULL);
}