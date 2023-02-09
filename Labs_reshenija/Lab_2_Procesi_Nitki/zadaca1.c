#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int samoglaska(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        return 1;
    default:
        return 0;
    }
}

int main(int argc, char *argv[])
{

    FILE *fptr;

    if ((fptr = fopen(argv[1], "r")) == NULL)
    {
        printf("Fileot %s e prazen ili ne e pronajden, exiting.\n", argv[1]);
        exit(-1);
    }

    char stringy[1000], iter;
    int length;
    while (((iter = fgetc(fptr)) != EOF) && length<999)
    {
        stringy[length++] = iter;
    }
    stringy[length] = '\0'; // null terminate

    pid_t dete[2];

    if (argc < 2)
    {
        printf("Nedovolen broj na argumenti.\n");
        exit(-1);
    }

    for (int i = 0; i < 2; i++)
    {
        dete[i] = fork();
        if (dete[i] == 0)
            break;
    }

    if (dete[0] == 0)
    {
        printf("FIRST CHILD\n");
        int soglaski = 0;
        for (int i = 0; i < length; i++)
        {
            if (isalpha(stringy[i]))
            {
                if (!samoglaska(stringy[i]))
                {
                    soglaski++;
                }
            }
        }
        printf("Brojot na soglaski iznesuva: %d\n", soglaski);
    }
    else if (dete[1] == 0)
    {
        printf("SECOND CHILD\n");
        int samoglaski = 0;
        for (int i = 0; i < length; i++)
        {
            if (isalpha(stringy[i]))
            {
                if (samoglaska(stringy[i]))
                {
                    samoglaski++;
                }
            }
        }
        printf("Brojot na samoglaski iznesuva: %d\n", samoglaski);
    }
    else
    {
        printf("PARENT PROCESS\n");
        printf("Gi chekam decata\n");
        for (int i = 0; i < 2; i++)
        {
            wait(NULL);
        }
        printf("Se vratija doma\n");
    }

    return 0;
}