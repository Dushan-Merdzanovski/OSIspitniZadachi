#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_THREADS 5

int K;
int N;
int array[1000];
int found1;
int found2;
int pid1;
int pid2;

void *prebaraj(void *t)
{
    long tid = (long)t;
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        int indeks = rand() % N;
        printf("Thread %ld generated the index %d!\n", tid, indeks);
        if ((array[indeks] == K) && getpid() == pid1)
        {
            printf("Jas sum nitka %ld od procesot %d i go najdov elementot %d na pozicija %d!\n", tid, pid1, K, indeks);
            found1 = 1;
            //kill(pid2,-9);
        }
        if ((array[indeks] == K) && getpid() == pid2)
        {
            printf("Jas sum nitka %ld od procesot %d i go najdov elementot %d na pozicija %d!\n", tid, pid2, K, indeks);
            found2 = 1;
            //kill(pid1,-9);
        }
    }
    pthread_exit((void *)t);
}

int main(int argc, char *argv[])
{
    N = atoi(argv[1]);
    K = atoi(argv[2]);

    FILE *fptr;
    if ((fptr = fopen("lab3.txt", "r")) == NULL)
    {
        fprintf(stderr, "File lab3.txt can't be opened\n");
        return -1;
    }

    char c;
    int pom = 0;
    int iter = 0;
    while ((c = fgetc(fptr)) != EOF && iter < N)
    {
        if (isdigit(c))
        {
            pom = 10 * pom + (int)c;
        }
        if (c == ' ')
        {
            array[iter++] = pom;
            pom = 0;
        }
    } // ovde odi do N, t.e. argv[1]

    for (int i = 0; i < N; i++)
    {
        printf("%d ", array[i]);
    }

    pid1 = atoi(argv[3]);

    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    void *status;

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, prebaraj, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for (int j = 0; j < NUM_THREADS; j++)
    {
        printf("Jas sum procesot %d i ja cekam nitkata %d", getpid(), j);
        rc = pthread_join(threads[j], &status);
        if (rc)
        {
            printf("Error, return code from pthread_join is %d", rc);
            return -1;
        }
    }

    if ((getpid() == pid1) && (found1 == 0))
    {
        printf("Main thread from process %d completed. without finding the number. Exit.\n", getpid());
    }
    if ((getpid() == pid2) && (found2 == 0))
    {
        printf("Main thread from process %d completed. without finding the number. Exit.\n", getpid());
    }

    printf("Main thread from process %d completed. Exiting!\n", getpid());
    pthread_exit(NULL);
}