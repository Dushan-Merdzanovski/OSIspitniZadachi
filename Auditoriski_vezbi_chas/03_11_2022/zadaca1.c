// NITKI primer2, za pthread_join nesho gluposti
#include <stdio.h>
#include <pthread.h>
#define NULL ((void *)0)

void *func(void *t)
{
    int i = *(int *)t; // analogija so 10kata, kao int * i ke vrati adresa, *int * ke vrati 10ka integer
    printf("Ja sum nitka so ID %d\n", i + 1);
    pthread_exit(NULL);
}
// OSIX nitki: 2 nitki , na dvete ke isprati reden broj neso idk
int main(int argc, char *argv[]) // nema da gi koristi ko argumenti, ama mora da gi pratime
{
    int i;
    pthread_t nitki[5];

    for (i = 0; i < 5; i++)
    {
        pthread_join(nitki[i], NULL);
        printf("Pristigna nitka %d\n",i);
    }
    
    return 0;
}