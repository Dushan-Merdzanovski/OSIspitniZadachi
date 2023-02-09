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
#include <fcntl.h>

// 2 kolokvium 2020/2021 verzija 2 grupa 1

/* 1. Да се напише C програма за комуникација помеѓу три процеси. Процесите комуницираат преку
заедничка меморија, притоа сите три процеси, како прв аргумент, го добиваат клучот за комуникација.
Првиот процес, како втор аргумент добива име на датотека чија што содржина треба да ја испраќа до
другите два процеси преку заедничката меморија. Првиот процес запишува 100 бајти од датотека во
меморијата, запишува колку бајти има запишано и им сигнализира на двата процеси дека има нешто
запишано во меморијата. Потоа, првиот процес чека другите два процеси да завршат работа и да му
сигнализираат да стави нови податоци во меморијата. Доколку нема 100 бајти, првиот процес запишува
колку што има преостанато во датотеката, им кажува на другите два процеси колку бајти има запишано
и ги запишува преостанатите бајти. Вториот и третиот процес ги изминуваат податоците што ги
запишува првиот процес во заедничката меморија, притоа вториот процес брои колку букви има,
третиот процес брои колку цифри има запишано во меморијата. Откако ќе завршат со броење и двата
процеси сигнализираат дека се завршени и чекаат нови 100 бајти за броење. Чим добијат помалку од 100
бајти, тоа значи дека тие се последни, ги бројат и тие, печатат на екран колку изброиле и завршуваат.  */

#define READ_MEM_SIZE 100

int main(int argc, char *argv[]) {
    int key = atoi(argv[1]);
    char name_dat[10], tmp[5];
    char *memory;
    char memory_array[100];
    int id, i, bytes_read;
    char c;

    strcpy(name_dat, argv[2]);
    id = shmget(key, READ_MEM_SIZE + 5, 0644 | IPC_CREAT); // 100B + 1B sync + 4B size
    if(id == -1) {
        printf("neuspesno dobivanje pristap");
    }
    memory = shmat(id, NULL, 0);
    memory[0] = '0'; // 0 e locked
    strncpy(memory + 1, "0", 4);

    FILE *fptr;

    if ((fptr = fopen(name_dat, "r")) == NULL) {
        printf("Nemozam da ja otvoram %s za citanje\n", name_dat);
        return (1);
    }

    memory[0] = '3'; // 3 e unlocked za proces 1
    while(1) {
        if (memory[0] == '3') {
            i = 0;
            memory[0] = '0'; // 0 e locked
            while (((c = fgetc(fptr)) != EOF) || (i < READ_MEM_SIZE)) {
                memory[5 + i] = c;
                i++;
            }
            tmp[4] = 0;
            sprintf(tmp, "%d", i);
            strncpy(memory + 1, tmp, 4);
            memory[0] = '1'; // 1 e unlocked za proces 2 i 3
            if (i < READ_MEM_SIZE) {
                break;
            } 
        } else {
            sleep(1);
        }
    }
    fclose(fptr);
    return 0;
}