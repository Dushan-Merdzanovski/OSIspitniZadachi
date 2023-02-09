#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// PIPELINES // ova e aud10_zad04 

/*Задача 1) Да се напише програма која ќе креира начин на комуникација помеѓу родителот и
дете процесот преку концепт на цевки. Сите податоци што ќе се обиде да ги
запише на екран татко процесот да се препратат како влезни податоци на дете
процесот. Дете процесот потоа треба да додаде тараба “#” пред секој податок
што ќе го запише родителот на екран. */

int main()
{
    pid_t pid;
    int mypipe[2];
    char memorija[512];
    int fd, broj;
    if (pipe(mypipe))
    {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    pid = fork();
    if (pid == (pid_t)0)
    {
        close(mypipe[1]);
        if (dup2(mypipe[0], 0) == -1)
        {
            printf("Neuspeav da dupliciram vo 0\n");
            return 0;
        }
        scanf("%s%d", memorija, &broj);
        printf("#%s %d", memorija, broj);
        return EXIT_SUCCESS;
    }
    else if (pid < (pid_t)0)
    {
        fprintf(stderr, "Neuspeshen FORK.\n");
        return EXIT_FAILURE;
    }
    else
    {
        close(mypipe[0]);
        if (dup2(mypipe[1], 1) == -1)
        {
            printf("Neuspeav da dupliciram vo 1\n");
            return 0;
        }
        printf("Poraka\n");
        printf("%d\n", 15);
        return EXIT_SUCCESS;
    }
}