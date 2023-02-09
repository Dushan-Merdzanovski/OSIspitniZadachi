#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("PID: %d\n", getpid());
   /*  int i;
    for (int i = 0; fork(); i++)
    {
        if (i == 4)
            break;

        printf("PID: %d i = %d\n", getpid(), i);
    } */

    int i;
    for (int i = 0; i < 4; i++)
    {
        if (fork())
            break;  
        printf("PID: %d i = %d\n", getpid(), i);
    }

    return 0;
}