#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Nedovolni argumenti na cmd line.\n");
        return -1;
    }

    pid_t dete[2];

    for (int i = 0; i < 2; i++)
    {
        dete[i] = fork();
        if (dete[i] == 0)
            break;
    }

    if (dete[0] == 0)
    {
        char pid1[20];
        sprintf(pid1, "%d", getpid());
        printf("Jas sum PRVO dete proces i ke ja izvrsam programata.\n");
        execlp("./zadaca22", "./zadaca22", argv[1], argv[2],pid1, NULL);
        printf("PRVO Neuspesno se povika naredbata ./zadaca22\n");
    }
    else if (dete[1] == 0)
    {
        char pid2[20];
        sprintf(pid2, "%d", getpid());
        printf("Jas sum VTORO dete proces i ke ja izvrsam programata.\n");
        execlp("./zadaca22", "./zadaca22", argv[1], argv[2],pid2, NULL);
        printf("VTORO Neuspesno se povika naredbata ./zadaca22\n");
    }
    else
    {
        printf("PARENT PROCESS\n");
        printf("Gi chekam decata\n");
        for (int i = 0; i < 2; i++)
        {
            wait(NULL);
        }
    }
    return 0;
}