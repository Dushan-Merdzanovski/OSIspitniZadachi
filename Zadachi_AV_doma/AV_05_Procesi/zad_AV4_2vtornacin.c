/* Задача 2: Да се напише програма која како аргумент добива команда која треба да ја
изврши. Татко процесот треба на екран да ги испишува секундите поминати од
започнување на програмата до крајот. */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    pid_t dete;
    int i = 0;
    dete = fork();
    if (dete == 0)
    {
        // dete proces
        execvp(argv[1], &argv[1]);
        printf("neuspesen povik\n");
    }
    else
    {
        // roditel proces
        while (1)
        {
            if (waitpid(dete, NULL, WNOHANG) == dete)
            {
                break;
            }
            sleep(1);
            i++;
            printf("pominaa %d sekundi\n", i);
        }
    }
    printf("Zavrshi deteto, mu trebase %d sekundi\n", i);
    return 0;
}