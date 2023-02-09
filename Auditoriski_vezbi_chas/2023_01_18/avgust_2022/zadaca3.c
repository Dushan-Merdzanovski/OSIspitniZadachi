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

int main(int argc, char *argv[]) {
    int X = 0, Y, counter = 0;
    pid_t dete, kill_dete;
    int i;

    dete = fork();

    if (dete == 0) {
        //dete proces
        execvp(argv[1], &argv[1]);
    }

    // roditel proces, sigurno samo on ke vleze nadole
    while (waitpid(dete, NULL, WNOHANG) != dete) {
        sleep(1);
        X++;
    }   

    for (i = 0; i < 99; i++) {
        dete = fork();
        // dete proces
        if (dete == 0) {
            execvp(argv[1], &argv[1]);
        }

        //roditel proces
        Y = 0; // aktivno
        while (waitpid(dete, NULL, WNOHANG) != dete) {
            sleep(1);
            Y++;
            if (Y > X) {
                kill_dete = fork();
                if (kill_dete == 0) {
                    execlp("kill", "kill", "-9", itoa(dete), NULL); // mozhe i syscall kill(dete);
                }
                counter++;
                break;
            }
        }
        if (Y < X) {
            X = Y;
        } 
    }

    printf("%d procesi bea prekinati vo izvrshuvanje\n", counter);
    return 0;
}