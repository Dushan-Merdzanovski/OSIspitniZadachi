#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 1. Да се напише програма во С каде ќе се овозможи извршување на процесите на начин каков што е
прикажан на сликата. При првото извршување на „argv[1]“ процесот, стандардниот влез е од тастатура,
додека пак при второто извршување на стандарден влез добива податоци од првото извршување на
„argv[2]“ и т.н. */

// argv[1] | argv[2] | argv[1] | argv[2]
int main(int argc, char **argv)
{
    pid_t dete1, dete2, dete3;
    int p1[2], p2[2], p3[2];
    pipe(p1);
    dete1 = fork();
    if (dete1 > 0)
    {
        // roditel proces
        close(p1[0]);
        dup2(p1[1], 1);
        execlp(argv[1], argv[1], NULL);
    }
    else
    {
        // prvo dete
        pipe(p2);
        dete2 = fork();
        if (dete2 > 0)
        {
            // dete 1
            close(p1[1]);
            close(p2[0]);
            dup2(p1[0], 0);
            dup2(p2[1], 1);
            execlp(argv[2], argv[2], NULL);
        }
        else
        {
            // dete 2
            pipe(p3);
            dete3 = fork();
            if (dete3 > 0)
            { // dete 2
                close(p2[1]);
                dup2(p2[0], 0);
                close(p3[0]);
                dup2(p3[1], 1);
                execlp(argv[1], argv[1], NULL);
            }
            else
            {
                // dete 3
                close(p3[1]);
                dup2(p3[0], 0);
                execlp(argv[2], argv[2], NULL);
            }
        }
    }
    return 0;
}