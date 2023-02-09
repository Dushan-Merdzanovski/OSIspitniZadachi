// NITKI primer
#include <stdio.h>
#include <pthread.h>
#define NULL ((void *)0)

void *func(void *t)
{
    int i = *(int *)t; // analogija so 10kata, kao int* i ke vrati adresa, *int* ke vrati 10ka integer
    printf("Ja sum nitka so ID %d\n", i + 1);
    pthread_exit(NULL);
}
// OSIX nitki: 2 nitki, na dvete ke isprati reden broj neso idk
int main(int argc, char *argv[]) // nema da gi koristi ko argumenti, ama mora da gi pratime
{
    int i;
    pthread_t nitki[5];

    for (i = 0; i < 5; i++) // i < 5 e zadaca1
    {
        int rc = pthread_create(&nitki[i], NULL, func, (void *)&i); // 4toto kastira int pokazuvach vo void*
        printf("rc = %d\n", rc);
    }
    
    return 0;
}