#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
/* 2. Да се напише C програма за комуникација помеѓу три процеси. Процесите комуницираат преку
pipe комуникација, така што првиот процес комуницира со вториот процес преку еден pipe, додека пак
вториот комуницира со третиот процес преку втор pipe. Првиот процес чита цели броеви од тастатура и
број по број ги испраќа на вториот процес. Вториот процес, ги чита броевите, број по број, пресметува
просек на моментално пристигнатите броеви, така што за секој нареден број се наново пресметува
просекот вклучувајќи го и новиот број. Просекот на дотогаш внесените броеви го испраќа на третиот
процес и чека нов број. Третиот процес, ги чита просек по просек и на екран го печати првиот просек, а
секој нареден просек печати колава е разликата од претходниот просек. 
Пример: Прв процес чита 12, втор процес пресметува 12, трет процес печати 12
Потоа, прв процес чита 8, втор процес пресметува 10, трет процес печати 10-12= -2
Потоа, прв процес чита 5, втор процес пресметува 25/3 = 6, трет процес печати 6-10=-4
И така натаму */

int main() {
    char c;
    pid_t dete1, dete2;
    int p1[2], p2[2];
    int broj;
    
    int ekran = dup(1);
    if (pipe(p1)) {
        printf("First pipe failed!\n");
        return 1;
    }

    dete1 = fork();
    if (dete1 == 0) {
        // proces 2
        if(pipe(p2)) {
            printf("Second pipe failed!\n");
            return 1;
        }

        dete2 = fork();
        if (dete2 == 0) {
            // proces 3
            /* close(p1[0]);
            close(p1[1]); */
            close(p2[1]);

            dup2(p2[0], 0);

            int counter = 1;
            int prethodenprosek = 0;
            int tekovenprosek = 0;

            while (counter <= 3) {
                scanf("%d", &tekovenprosek);

                printf("Tekoven prosek vo third proces: %d\n",tekovenprosek);
                printf("Third process: %d\n", tekovenprosek - prethodenprosek);
                prethodenprosek = tekovenprosek;
                
                counter++;
            }
        } else {
            // proces 2
            close(p1[1]);
            close(p2[0]);
            
            dup2(p1[0], 0);
            
            int zbir = 0;
            int prosek = 0;
            int counter = 1;

            int inbroj;
            dup2(p2[1], 1);

            while (counter <= 3) {
                scanf("%d", &inbroj);
                
                fflush(stdout);

                zbir += inbroj;
                prosek = zbir / counter; 
                printf("%d\n", prosek);

                counter++;
            }
        }

    } else {
        // proces 1, roditel
        close(p1[0]);
        int counter = 1;
        while (counter <= 3) {
            printf("Vnesete broj od tastaturata\n");
            fflush(stdout);

            dup2(p1[1], 1);
            scanf("%d", &broj);
            printf("%d\n", broj);
            fflush(stdout);
            /* write(1, &broj, 4); */

            dup2(ekran, 1);
            printf("Prv proces chita: %d\n", broj);
            fflush(stdout);
            counter++;
        }
    }
    return 0;
}

/* fflush(stdin);
    fflush(stdout); */