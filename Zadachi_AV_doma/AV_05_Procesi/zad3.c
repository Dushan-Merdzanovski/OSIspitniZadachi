/*Татко процесот ќе ги креира деца процесите. Секое дете процес ќе испише на екран кој 
му е татко процес, и кое му е сопственото ID. Татко процесот чека секое од децата 
процеси да завршат и на крај печати дека и тој се уништува. */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{

    pid_t dete[3];

    int i;
    for (int i = 0; i < 3; i++)
    {
        dete[i] = fork();
        if (dete[i] == 0)
            break;
    }

    if (dete[0] == 0)
    {
        printf("Jas sum prvoto dete, mojot PID e %u, a roditel PPID e %u\n", getpid(), getppid());
        return 0;
    }
    else if (dete[1] == 0)
    {
        printf("Jas sum vtoroto dete, mojot PID e %u, a roditel PPID e %u\n", getpid(), getppid());
        return 0;
    }
    else if (dete[2] == 0)
    {
        printf("Jas sum tretoto dete, mojot PID e %u, a roditel PPID e %u\n", getpid(), getppid());
        return 0;
    }
    else
    {
        printf("Ja sum roditel proces, %u\n", getpid());
    }

    printf("Gi chekam decata da se vratat doma\n");
    for(int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("Se vratija doma.\n");

    return 0;
}