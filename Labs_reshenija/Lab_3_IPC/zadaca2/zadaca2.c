#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int z;
    printf("Vnesete broj na deca Z\n");
    scanf("%d", &z);

    pid_t deca[z];
    int i;
    key_t kluc = 1234;
    for (i = 0; i < z; i++)
    {
        deca[i] = fork();
        if (deca[i] == 0)
            break;
    }

    int id;
    if ((id = shmget(kluc, 100, IPC_CREAT | 0666)) == -1) // shmget na sekoj proces posebno!!!!!! smeni go ova, i vo roditel napraj go ednash
    { // == -1
        printf("Neuspeshno dobivanje pristap do memorijata.\n");
        exit -1;
    }

    char *mem;
    if (i < z)
    {
        // dete
        mem = shmat(id, NULL, 0);
        if (mem == NULL)
        {
            printf("Neuspesno prikacuvanje na memorijata\n");
            return 0;
        }

        char *argumenti_list[argc];
        for (int m = 0; m < argc - 1; m++)
        {
            strcpy(argumenti_list[m], argv[m + 1]);
        }
        argumenti_list[argc - 1] = NULL;

        while (1)
        {
            if (mem[0] != 'l')
            {
                mem[0] = 'l';
                /* printf("Index %d dete\n", getpid()); */
                execvp(argv[1], argumenti_list);
                printf("Ne se izvrshi naredbata.\n");
                break;
            }
            else
            {
                sleep(1);
            }
        }
    }
    else
    { // roditel
        int sekundi = 0;
        int proces;
        int procesi[i];
        mem = shmat(id, NULL, 0);
        if (mem == NULL)
        {
            printf("Neuspesno prikacuvanje na memorijata\n");
            return 0;
        }

        while (1)
        {
            /* for (int i = 0; i < z; i++){}
                proces = wait(NULL);
                if (proces) {
                    if (mem[0] == 'l') {
                        mem[0] = 'u';
                    }
                } */

            for (int i = 0; i < z; i++)
            {
                procesi[i] = waitpid(deca[i], NULL, WNOHANG); // CHEKAJ GO SEKOE DETE POSEBNO, SPORED INDEKS ZAPISHUVAJ VO MEMORIJATA. Setiraj prvo -1 pred da pochnat site, pa menuvaj vo memorija posle sekoj waitpid, i++ pravi mu za da znae koe sledno dete treba da se izvrshi.
                if (procesi[i])
                {
                    if (mem[0] == 'l')
                    {
                        mem[0] = 'u';
                    }
                }
            }

            int j;
            for (j = 0; j < z; j++)
            {
                if (procesi[j] == 0)
                {
                    break;
                } /* else {

                }  */
            }
            if (j == z)
            {
                break;
            }
            sleep(1);
            sekundi++;
        }
        printf("Na deca procesite vkupno im trebale %d sekundi,\n", sekundi);
        printf("Decata se vratija. Roditel process is done.\n");
        shmdt(mem);
        shmctl(id, IPC_RMID, 0);
    }

    return 0;
}