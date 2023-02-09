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

// ISPIT JANUARI 2022
// zadacha 3

int main(int argc, char*argv[]) {
    int arg[100];
    int search[100];
    // 1024B memorija kje koristime, + 5 bajti za sync i used
    // 0tiB - sync (eden bajt), (4bajti za used )- kolku se ikoristeni.
    key_t kluc = 1200;
    int N = argc - 1;
    int broj;
    int kolku, deliteli;
    pid_t dete;
    int i;
    int brDeca = 0;
    for (i = 0; i < N; i++) {
        arg[i] = atoi(argv[i+1]);
    }

    int id;
    id = shmget(kluc, 1029, 0644 | IPC_CREAT); //0644
    if(id == -1) {
        printf("neuspesno dobivanje pristap");
    }

    char *mem = shmat(id, NULL, 0);  // OVDE MOZHE KAKO INTEGER TIP DA SE KORISTI, POPROSTO E VAKA!!! prvite 2 kje bea zafateni, prviot za sync, vtoriot kolku se zapishani, celo vreme so mem[1]++ ke zgolemuvashe
    // prereshi ja vaka so integer mem. mnogu polesno
    mem[0] = '0'; // 0 e unlocked
    strncpy(mem + 1, "0", 4); // 0 iskoristeni bajti, ama mu vika 4 bajti da iskopira

    printf("Vnesuvaj deca:\n");
    fflush(stdout);

    while (scanf("%d", &broj) == 1) { // scanf vrakja 1 ako se vnese cel broj
        brDeca++;
        dete = fork();
        if (dete == 0) {
            break;
        }
    }

    if (dete == 0) {
        // deca, zapishuvanje
        kolku = deliteli = 0;
        for (i = 0; i < N; i++) {
            if (arg[i] == broj)
                kolku++;
            if (arg[i] % broj == 0)
                deliteli++;
        }
        int id;
        id = shmget(kluc, 1029, 0644);
        if (id < 0)
        { // == -1
            printf("Neuspeshno dobivanje pristap do memorijata.  \n");
            return 0;
        }
        char *mem = shmat(id, NULL, 0);
        while (mem[0] == '1') { // while locked
            sleep(1);
        }
        mem[0] = '1'; // ja zaklucuvame memorijata
        char used[5];
        strncpy(used, mem + 1, 4);
        used[4] = 0; // nul terminator
        int u = atoi(used);

        strncpy(mem + 5 + u, itoa(broj), strlen(itoa(broj)));
        u+=strlen(itoa(broj));
        mem[u + 5] = ' ';
        u++;

        strncpy(mem + 5 + u, itoa(kolku), strlen(itoa(kolku)));
        u+=strlen(itoa(kolku));
        mem[u + 5] = ' ';
        u++;

        strncpy(mem + 5 + u, itoa(deliteli), strlen(itoa(deliteli)));
        u+=strlen(itoa(deliteli));
        mem[u + 5] = ' ';
        u++;

        strcpy(mem + 1, itoa(u)); // zgresheno mu beshe na goki od mem + 5 imashe pishano
        mem[0] = '0'; // ja otkluchuvame memorijata
    } 
    while (brDeca >= 0) {
        wait(NULL);
    }
    mem[0] = '2';
    shmdt(mem);
    return 0;
}