/* Да се напише програма која ќе креира 4 нитки. Секоја од нитките извршува сложена
математичка функција. Главната нитка треба да ги дочека сите нитки да завршат, па
потоа таа да заврши. */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4

void *BusyWork(void *t)
{
    int i;
    long tid;
    double result = 0.0;
    tid = (long)t;
    pthread_t ttid = pthread_self();
    printf("Thread %ld starting with tid=%lu...\n", tid, ttid);
    for (i = 0; i < 1000000; i++)
    {
        result = result + sin(i) * tan(i);
    }
    printf("Result: %lf\n", result);
    pthread_exit((void *)t);
}

int main(int argc, char *argv[])
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_attr_destroy(&attr);
    for (t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_join(thread[t], &status);
        if (rc)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
    }
    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}