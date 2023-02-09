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

// PRODOLZUVA ZADACA 3 TUKA, OVOJ E DRUGIOT PROCES SHTO KE KOMUNICIRA

int main() {
    int id;
    int kluc = 1200;
    id = shmget(kluc, 1029, 0644);
    if (id == -1)
    { // == -1
        printf("Neuspeshno dobivanje pristap do memorijata.  \n");
        return 0;
    }
    char *mem = shmat(id, NULL, 0);

    while (mem[0] != '2') { // na 2ka znaeme deka zavrshile site procesi od drugata programa
        sleep(1); 
    }
    char s[5];
    strncpy(s, mem + 1, 4);
    s[4] = 0; // nul terminator
    int size = atoi(s);

    int skip = 5;
    
    while (skip <= size) {
        int broj;
        int deliteli, kolku;
        char b[10];
        int i = 0;
        while (mem[skip] != ' ') {
            b[i] = mem[skip];
            i++;
            skip++;
        }
        b[i] = 0; // nul terminator
        broj = atoi(b);
        skip++;

        i = 0;
        while (mem[skip] != ' ') {
            b[i] = mem[skip];
            i++;
            skip++;
        }
        b[i] = 0;
        kolku = atoi(b);

        i = 0;
        while (mem[skip] != ' ') {
            b[i] = mem[skip];
            i++;
            skip++;
        }
        b[i] = 0;
        deliteli = atoi(b);

        printf("Brojot %d go ima %d pati, so $d deliteli", broj, kolku, deliteli);
    }
    return 0;
}