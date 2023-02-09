#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* 3. Да се напише C програма која како аргумент добива наредба (без аргументи) што треба
да се изврши. Татко процесот креира дете процес кое што ја извршува наредбата, притоа целиот
излез од наредбата се запишува во датотека со име „izlez.txt“. Татко процесот чека дете
процесот да заврши, а потоа креира 6 нитки кои што ќе ја пребаруваат датотеката „izlez.txt“.
Првите 5 нитки бројат колку самогласки има во датотеката, додека пак 6тата нитка гледа колку
знаци има различни од букви и бројки. Најпрво татко процесот, пред да ги креира нитките, ја
исчитува содржината на целата датотека и во низа од најмногу 100 знаци ја сместува
содржината од датотеката. Секоја од нитките ја извршува функцијата „prebaraj“ за изминување
на низата и броење на соодветните знаци. Кога сите нитки ќе завршат, татко процесот (главната
нитка) на екран печати колку знаци имало од секоја самогласка а колку знаци различни од букви
и бројки. */


char text[100];
int length = 0;
typedef struct {
    int id;
    int samoglaski;
    int brojnotalnum;
}threadstruct;

void *izbroi(void* id) {
    threadstruct *thr = (threadstruct*) id;

    if (thr->id == 0) {
        for (int i = 0; i < length; i++) {
            if (isalpha(text[i]) && (text[i]=='a' || text[i]=='A')) {
                thr->samoglaski++;
            }
        }
    } else if (thr->id == 1) {
        for (int i = 0; i < length; i++) {
            if (isalpha(text[i]) && (text[i]=='e' || text[i]=='E')) {
                thr->samoglaski++;
            }
        }
    } else if (thr->id == 2) {
        for (int i = 0; i < length; i++) {
            if (isalpha(text[i]) && (text[i]=='i' || text[i]=='I')) {
                thr->samoglaski++;
            }
        }
    } else if (thr->id == 3) {
        for (int i = 0; i < length; i++) {
            if (isalpha(text[i]) && (text[i]=='o' || text[i]=='O')) {
                thr->samoglaski++;
            }
        }
    } else if (thr->id == 4) {
        for (int i = 0; i < length; i++) {
            if (isalpha(text[i]) && (text[i]=='u' || text[i]=='U')) {
                thr->samoglaski++;
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            if (!isalnum(text[i])) {
                thr->brojnotalnum++;
            }
        }
    }
    pthread_exit(NULL); 
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Nevaliden broj na argumenti\n");
        return -1;
    }

    char naredba[30];
    strcpy(naredba,argv[1]);

    pid_t dete;

    dete = fork();

    if (dete == 0) {
        strcat(naredba,">izlez.txt");
        printf("NAREDBA:%s\n",naredba);

        char *binaryPath = "/bin/bash";
        char *arg1 = "-c";
        execlp(binaryPath, binaryPath, arg1, naredba, NULL);
        printf("Neuspeshno izvrshuvanje na naredbata.\n");
        return -1;
    } else {
        wait(NULL);

        FILE *fptr;

        if (!(fptr = fopen("izlez.txt","r"))) {
            printf("Ne mozhe da se otvori datotekata\n");   
            return -1;
        }

        char c;

        while (((c = fgetc(fptr)) != EOF) && (length < 99)) {
            text[length] = c;
            length++; // globalna
        }

        pthread_t threads[6];
        threadstruct objs[6];

        for (int i = 0; i < 6; i++) {
            objs[i].brojnotalnum = objs[i].samoglaski = 0;
            objs[i].id = i;
            pthread_create(&threads[i],NULL,izbroi,(void*)&objs[i]);
        }

        for (int i = 0; i < 6; i++) {
            pthread_join(threads[i],NULL);
        }

        for (int i = 0; i < 6; i++) {
            if (i == 0)
                printf("Samoglaskata A ja ima: %d pati\n",objs[i].samoglaski);
            else if (i == 1)
                printf("Samoglaskata E ja ima: %d pati\n",objs[i].samoglaski);
            else if (i == 2)
                printf("Samoglaskata I ja ima: %d pati\n",objs[i].samoglaski);
            else if (i == 3)
                printf("Samoglaskata O ja ima: %d pati\n",objs[i].samoglaski);
            else if (i == 4)
                printf("Samoglaskata U ja ima: %d pati\n",objs[i].samoglaski);
            else
                printf("Znaci razlicni od alnum ima: %d pati\n",objs[i].brojnotalnum);
        }
    }

    return 0;
}