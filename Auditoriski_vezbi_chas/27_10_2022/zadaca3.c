#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t dete[3];

    int i;
    for (int i = 0; i < 3; i++)
    {
        dete[i] = fork(); //
        if (dete[i] == 0)
            break; // nema da prodolzi so for-ot, samo roditelot ke prodolzi da gi kreaira svoite dete procesi, zadrzhuva na 0
    }

    // i = 0 prvo dete
    // i = 1 vtoro dete
    // i = 2 treto dete
    // i = 3 roditel proces
    if (dete[0] == 0)
    {
        printf("Ja sum prvoto dete, mojot proces ID e %u, a roditelot mi e %u\n", getpid(), getppid());
        return 0;
    }
    else if (dete[1] == 0)
    {
        printf("Ja sum vtoroto dete, mojot proces ID e %u, a roditelot mi e %u\n", getpid(), getppid());
        return 0;
    }
    else if (dete[2] == 0)
    {
        printf("Ja sum tretoto dete, mojot proces ID e %u, a roditelot mi e %u\n", getpid(), getppid());
        return 0;
    }
    else
    {
        printf("Ja sum roditel proces %u, gi chekam decata", getpid());
    }

    printf("Gi chekam decata da se vratat doma\n");
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }
    printf("Se vratija doma.\n");

    return 0;
}