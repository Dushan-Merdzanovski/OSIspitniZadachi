#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Zadaca2, fajl 2021_2022_OS_Vtor_kolok_18_1_2022

int main () {
    pid_t dete1, dete2;
    int p1[2], p2[2];
    int t1, t2;

    printf("Vnesi ja vrednosta na t1\n");
    scanf("%d", &t1);
    fflush(stdin);
    printf("Vnesi ja vrednosta na t2\n");
    scanf("%d", &t2);

    if (t1 == 0) {
        pipe(p1);
    }

    dete1 = fork();

    if (dete1 == 0) {
        if (t1 == 0) {
            close(p1[1]);
            dup2(p1[0], 0);
        }
        if (t2 == 0) {
            pipe(p2);
        }
        dete2 = fork();

        if (dete2 == 0) {
            // proces 3
            if (t2 == 0) {
                close(p2[1]);
                dup2(p2[0], 0);
            }
            execlp("wc", "wc", "-c", NULL);
        } else {
            // proces 2
            if (t2 == 0) {
                close(p2[0]);
                dup2(p2[1], 1);
            }
            execlp("tail", "tail","-9",NULL);
        }
    } else {
        // proces 1
        if (t1 == 0) {
            close(p1[0]);
            dup2(p1[1], 1);
        }
        execlp("cat", "cat", "./zadaca2.c", NULL);
    }
    return 0;
}