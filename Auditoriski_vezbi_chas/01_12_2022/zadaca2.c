#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/mman.h>
// MEMORISKO MAPIRANJE

/*
Да се напишат програми кои ќе комуницираат помеѓу себе користејќи
мемориско мапирање.
• Едната програма треба да ги смести сите парни броеви од 1 до 2000.
• Другата програма треба да ги прочита и испише на екран овие броеви.
• Да се овозможи механизам да втората програма ја повика првата
програма и почека додека заврши пред да пристапи до мапираната
меморија.
*/

int main(int argc, char *argv[])
{
    pid_t dete;
    int fd;
    int *p;
    int i, j;

    dete = fork();

    if (dete == 0)
    {
        // proces 1; ustvari vtoriot proces, ovoj zapishuva vo memorijata
        if ((fd = open("dat.txt", O_RDWR | O_CREAT, 00666)) == -1)
        {
            printf("ne se otvorila datotekata.\n");
            return 0;
        }

        if (ftruncate(fd, 1000 * (sizeof(int))) == -1)
        {
            printf("neuspesno proshiruvanje na memorijata\n");
            return 0;
        }

        p = mmap(NULL, 1000 * (sizeof(int)), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED)
        {
            printf("Neuspesno\n");
            return 0;
        }

        for (i = 2, j = 0; i <= 2000; i += 2, j++)
        {
            p[j] = i;
        }
        munmap(p, 1000 * (sizeof(int)));
    }
    else
    {
        wait(NULL);
        // proces 2; parent, go kreairal deteto t.e. proces 1
        if ((fd = open("dat.txt", O_RDWR | O_CREAT, 00666)) == -1)
        {
            printf("ne se otvorila datotekata.\n");
            return 0;
        }

        if (ftruncate(fd, 1000 * (sizeof(int))) == -1)
        {
            printf("neuspesno proshiruvanje na memorijata\n");
            return 0;
        }
        p = mmap(NULL, 1000 * (sizeof(int)), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED)
        {
            printf("Neuspesno\n");
            return 0;
        }

        for (i = 0; i <= 1000; i++)
        {
            printf("%d ", p[i]);
        }
        munmap(p, 1000 * (sizeof(int)));
    }
    return 0;
}