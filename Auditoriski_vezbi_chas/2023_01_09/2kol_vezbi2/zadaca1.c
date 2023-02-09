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

// ovaa e LAB3 IPC: zadacha 2, od nekoj fajl 2021_2022_OS_Vtor_kolok_18_1_2022

int main(int argc, char *argv[]) {
    int i, Z;
    
    int sekundi = 0;
    
    printf("Vnesi ja vrednosta na Z\n");
    scanf("%d",&Z);
    int cekaj = 0;
    pid_t deca[Z];
    char *mem;

    key_t kluc = 1200;
    int id;
    id = shmget(kluc, 1, 0644 | IPC_CREAT); //0644
    if(id == -1) {
        printf("neuspesno dobivanje pristap");
    }
    mem = shmat(id, NULL, 0);
    mem[0] = 0;
    
    for (i = 1; i <= Z; i++) {
        deca[i-1] = fork();
        if(deca[i-1] == 0) {
            break;
        }
    }

    if (i > Z) {
        // roditel
        while(cekaj <= Z) { // vidi dali <= ili <
            cekaj++;
            mem[0] = cekaj;
            while(waitpid(deca[cekaj-1], NULL, WNOHANG) != deca[cekaj-1]) {
                sleep(1);
                sekundi++;
            }
        }
        printf("Na decata im trebashe %d sekundi da zavrshat\n",sekundi);
    } else {
        // deca 1 do Z
        id = shmget(kluc, 1, 0644); //bez ipc creat
        if(id == -1) {
            printf("neuspesno dobivanje pristap");
        }
        mem = shmat(id, NULL, 0);

        while (mem[0] != i) {
            sleep(1);
        }

        execvp(argv[1], &argv[1]);
        return 0;
  }
}
        /*
        vaka za poishe argumenti 
        char *argumenti_list[argc];
        for (int m = 0; m < argc - 1; m++)
        {
            strcpy(argumenti_list[m], argv[m + 1]);
        }
        argumenti_list[argc - 1] = NULL;
        execvp(argv[1], argumenti_list);
        printf("Ne se izvrshi naredbata.\n"); */