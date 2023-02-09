#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#define NUM_THREADS 5

int found;
int N;
int K;
pid_t dete;

void *prebaraj(void *niza)
{
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        int el = ((int *)niza)[i];
        int indeks = rand() % N;
        if (el == K)
        {
            found = 1;
            printf("Proces1 go najde element %d na pozicija %d \n", el, indeks);
            kill(dete, SIGKILL);
            pthread_exit(NULL);
            break;
        }
    }
}

int main(int agrc, char *argv[])
{

    N = atoi(argv[1]);
    K = atoi(argv[2]);

    FILE *fptr;

    if ((fptr = fopen("lab3.txt", "r")) == NULL)
    {
        fprintf(stderr, "File lab3.txt can't be opened\n");
        return -1;
    }

    int array[N];
    char c;
    int pom = 0;
    int iter = 0;
    while ((c = fgetc(fptr) != EOF) && (iter < N))
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
    }
    fclose(fptr);

    dete = fork();

    if (dete == 0)
    {
        execvp("./zadaca22", argv);
    }
    else
    {
        int rc;
        long t;
        void *status;
        pthread_t threads[NUM_THREADS];
        for (int i = 0; i < NUM_THREADS; i++)
        {
            rc = pthread_create(&threads[i], NULL, prebaraj, (void *)array);
            if (rc)
            {
                printf("Error creating a thread %d\n", rc);
                exit(-1);
            }
        }

        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }

        if (!found)
        {
            printf("Proces1 ne go najde brojot.\n");
            pthread_exit(NULL);
        }
        pthread_exit(NULL);
    }
    return 0;
}
