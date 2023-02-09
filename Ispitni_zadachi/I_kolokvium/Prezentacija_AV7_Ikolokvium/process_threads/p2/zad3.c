/* 
Задача 3: Да се напише програма во C која работи со процеси и нитки. Главната програма (родител
процесот) добива низа од наредби кои треба да ги изврши како аргументи од командна линија. 
Родител процесот треба, најпрво, да креира онолку деца процеси колку што има наредби
наведено од командна линија (наредбите се без аргументи). Пота, треба да креира онолку нитки, 
колку што има наредби, така што, секоја нитка ќе чека и ќе брои колку секунди му било потребно
на соодветниот процес да заврши. Тоа значи дека, првата нитка ќе биде задолжена за првата
наредба т.е. за првиот процес, втората за вториот и т.н. Секоја нитка брои колку време се
извршувал нејзиниот процес (наредба) и кога ќе заврши кажува колку вкупно секунди му требало
да заврши, а потоа и самата нитка завршува. Откако ќе завршат сите процеси/нитки, тогаш
главниот процес/нитка печати на екран колку време и требало на секоја наредба да се изврши.

БОНУС: главниот процес/нитка печати на екран колку време и требало на секоја наредба да се
изврши во растечки редослед според времето на завршување, најпрво да се отпечати која
наредба и требало најмалку време да заврши, па потоа следната наредба и т.н.
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

pid_t dete[10]; // zadadi si sam ova
int vreme[10];

void *cekaj(void* id) {
    int indx = *(int*) id;
    int counter=0;

    while(1) {
        if(waitpid(dete[indx],NULL,WNOHANG) == dete[indx]) {
            break;
        }
        sleep(1);
        counter++;
    }   
    printf("Na deteto %d mu trebaa %d sekundi da zavrshi\n",indx,counter);
    vreme[indx]=counter;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    int N = argc - 1;
    pthread_t threads[N];
    int K[10];

    int i;
    for (i = 0; i < N; i++) {
        dete[i] = fork();
        if(dete[i] == 0) {
            break;
        }
    }

    if (i < N) {
        execlp(argv[i+1],argv[i+1],NULL);
        printf("Neuspeshen povik na argv[%d] %s\n",i + 1,argv[i+1]);
    } else {
        for (int i = 0; i < N; i++) {
            K[i] = i; // indeksot na sekoj thread, za da mozhe iminjata i vreminjata da gi zima!
            pthread_create(&threads[i],NULL,cekaj,(void*)&K[i]);
        }

        for (int i = 0; i < N; i++){
            pthread_join(threads[i],NULL);
        }

        for (int j = 0; j < N; j++)
            wait(NULL);

        int vkupno = 0;
        for (int i = 0; i < N; i++) {
            printf("Na deteto %d mu trebaa %d sekundi da zavrshi.\n",i,vreme[i]);
        }

        // sort bonus
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                if (vreme[i] > vreme[j]) {
                    int temp = vreme[i];
                    vreme[i] = vreme[j];
                    vreme[j] = temp;

                    char temp1[30];
                    strcpy(temp1,argv[i+1]);
                    strcpy(argv[i+1],argv[j]);
                    strcpy(argv[j],temp1);
                }
            }
        }

        for (int i = 0; i < N ; i++) {
            printf("Na Komanda %s i trebaa %d sekundi.\n",argv[i+1],vreme[i]);
        }

    }   
    
    return 0;
}