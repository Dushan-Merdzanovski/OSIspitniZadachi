/*Задача:
Да се напише програма која ќе креира 5 нитки. Секоја од нитките да го отпечати на 
екран својот реден број. Дали при секое извршување на програмата, ист е редоследот 
на печатење на екран? Зошто? Од што зависи?*/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
    pthread_t t = pthread_self();
    int tid;
    tid = *((int *)threadid);
    printf("Hello World! It's me, %lu thread #%d \n", t, tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    int tid[NUM_THREADS];
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("In main: creating thread %ld\n", t);
        tid[t] = t;
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&tid[t]);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            return -1;
        }
    }
    pthread_exit(NULL);
}