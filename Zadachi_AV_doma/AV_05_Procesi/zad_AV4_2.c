/* Задача 2: Да се напише програма која како аргумент добива команда која треба да ја
изврши. Татко процесот треба на екран да ги испишува секундите поминати од
започнување на програмата до крајот. */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t dete;
    pid_t tatko;
    pid_t status = 0;
    dete = fork();
    int sekundi = 0;
    if (dete == 0)
    { // dete_proces
        execv(argv[1], &argv[1]);
        printf("Ne uspea povikot\n");
    }
    else
    { // tatko proces
        while (status == 0)
        {
            printf("Se izvrshuva %d sekundi\n", sekundi);
            sleep(1);
            sekundi++;
            status = waitpid(dete, NULL, WNOHANG);
        }
    }
    return 0;
}
