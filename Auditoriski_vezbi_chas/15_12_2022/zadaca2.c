#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/*
За дома: (taka se vika zadacata)
Да се напише програма која како аргумент добива команда со параметри која
треба да се изврши. Програмот треба да изврши редирекција на стандардниот
излез од програмата во датотека ekran.data. */

int main(int argc, char *argv[])
{
    /* int fd;

    if (fd = open("ekran.data",O_WRONLY) == -1) {
        printf("Neuspesno\n");
        return 0;
    }
    dup2(fd, 1);
    execvp(argv[1], &argv[1]);*/

    int i, dete[3], fd;
    for (int i = 0; i < 3; i++)
    {
        dete[i] = fork();
        if (dete[i] == 0)
            break;
    }

    if (i < 3)
    {
        int fd = open("ekran.data", O_WRONLY | O_APPEND); // O_APPEND da dodadat drugite deca na istata datoteka, bez append 3 pati istoto ke se desi, t.e. ke se prebrishat od drugite execs
        dup2(fd, 1);
        execvp(argv[1], &argv[1]); // daj go ls kako argument samo
    } else {
       /*  wait(NULL);
        wait(NULL);
        wait(NULL); */
    }

    return 0;
}