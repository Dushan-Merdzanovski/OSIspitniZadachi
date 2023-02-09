/* Да се напише програма во C која работи со процеси. Програмата (главниот
процес) треба да дозволи да се внесе целобројна вредност од тастатура К
(најмногу 100). Потоа, главниот процес треба да дозволи да се внесат К
наредби од тастатура, притоа секоја наредба што се внесува има име на
наредбата и три аргументи. Главниот процес, за секоја наредба внесена од
тастатура треба да креира дете процес, на кое ја испраќа наредбата (заедно
со трите аргументи), притоа, дете процесот треба да ја изврши таа наредба.
Секое од деца процесите, пред да ја изврши наредбата, одбира случаен број
од 1 до 20 (со наредбата rand()%20+1) и чека толку секунди пред да почне
да ја извршува наредбата. Дете процесот печати колку секунди ќе чека пред
да почне со чекање.
Главниот процес, ги чека деца процесите да завршат со извршување, потоа
печати на екран дека и тој завршува.
БОНУС: Главниот процес да измери колку секунди им требало на сите
деца да завршат со извршување. */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {
    int K;
    printf("Vnesete vrednost do 100\n");
    scanf("%d",&K);
    pid_t dete[20]; // zadadi sam kolku dete max da ima
    char naredba[30],n1[10],n2[10],n3[10];
    int i;
    for (i = 0 ; i < K; i++) {
        printf("Vnesete naredba so 3 argumenti za deteto %d.\n",i);
        scanf("%s %s %s %s",naredba,n1,n2,n3);
        dete[i] = fork();
        if(dete[i] == 0)
            break;
    }
    if (i < K) {
        srand(time(NULL));
        int cheka = rand() % 20 + 1;
        printf("Deteto %d so index: %d kje cheka %d sekundi.\n",getpid(),i,cheka);
        sleep(cheka);
        execlp(naredba,naredba,n1,n2,n3,NULL);
        printf("Naredbata %s ne se izvrshila.\n",naredba);
    } else {
        int sekundi = 0;
        int procesi[K];
        while(1) {
            for (int i = 0; i < K; i++) {
                procesi[i] = waitpid(dete[i],NULL,WNOHANG);  // 0 ako ushte trae, dete[i] ako zavrshil
            }
            for (int i = 0; i < K; i++) {
                if (procesi[i] == 0)
                    break;
            }
            if(i == K) {
                break;
            }
            sleep(1);
            sekundi++;
        }
        printf("Na procesite vkupno im trebale %d sekundi.\n",sekundi);
        printf("Decata se vratija. Roditel proces is done.\n");
    }

    return 0;
}