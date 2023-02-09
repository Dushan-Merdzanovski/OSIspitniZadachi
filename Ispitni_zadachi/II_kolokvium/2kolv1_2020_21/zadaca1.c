#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

/* #define MAX_X 1920
#define MAX_Y 1190
#define MIN_X 1080
#define MIN_Y 800 */

#define MAX_X 15
#define MAX_Y 5
#define MIN_X 5
#define MIN_Y 3

int main(int argc, char *argv[])
{
    int id, i, x_respart, y_respart, iterator = 0;
    key_t kluc;
    char *mem;
    ssize_t procitano;
    char resolution[11];

    if (argc != 4)
    {
        printf("Greshka pri povikuvanje na programata.\n");
        return 1;
    }

    if (strcmp(argv[1], "1") == 0)
    {
        kluc = atoi(argv[2]);
        id = shmget(kluc, 1922, 0644 | IPC_CREAT);
        if (id == -1)
        {
            printf("neuspesno dobivanje pristap");
        }
        mem = shmat(id, NULL, 0);
        mem[0] = '0'; // locked

        int fdin;
        if ((fdin = open(argv[3], O_RDONLY)) == -1)
        {
            printf("Ne mozam da ja otvoram %s za citanje\n", argv[1]);
            return 1;
        }

        read(fdin, resolution, 10);
        resolution[9] = 0;
        char respart[5];
        strncpy(respart, resolution, 4);
        respart[4] = 0;
        int x_respart = atoi(respart);
        strncpy(respart, resolution + 5, 4);
        respart[4] = 0;
        int y_respart = atoi(respart);

        if (!((x_respart <= MAX_X || x_respart > MIN_X) && (y_respart > MIN_Y || y_respart < MAX_Y)))
        {
            mem[0] = '4'; // unsupported rezolucija
            printf("Nepoddrzhana rezolucija");
            return 0;
        }

        strncpy(mem + 1, resolution, 9);
        mem[0] = '3'; // prakjam na proces 2, da go vnese prviot red so rezolucijata vo datotekata

        while (iterator < y_respart)
        {
            if (mem[0] == '1')
            {
                mem[0] = '0'; // locked
                read(fdin, mem + 1, x_respart);
                mem[x_respart + 1] = '\n';
                mem[0] = '2'; // prakjam na proces 2, da gi prochita slednite x_respart pikseli
                iterator++;
            }
            else
            {
                sleep(1);
            }
        }
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        kluc = atoi(argv[2]);
        id = shmget(kluc, 1922, 0644 | IPC_CREAT);
        if (id == -1)
        {
            printf("neuspesno dobivanje pristap");
        }
        mem = shmat(id, NULL, 0);

        int fdout;
        if ((fdout = open(argv[3], O_WRONLY | O_CREAT)) == -1)
        {
            printf("Ne mozam da ja otvoram %s za citanje\n", argv[1]);
            return 1;
        }

        while (iterator < y_respart)
        {
            if (mem[0] == '2')
            {
                mem[0] = '0';
                char bufferche[1921];
                char c;
                for (int i = 0; i < x_respart + 1; i++) {
                    c = mem[i + 1];
                    bufferche[i] = c - '0';
                }
                write(fdout, bufferche, x_respart + 1);

                mem[0] = '1'; // prakjam na proces 1, da gi vnese slednite x_respart pikseli
                iterator++;
            }
            else if (mem[0] == '3')
            {
                mem[0] = '0';

                strncpy(resolution, mem + 1, 9);
                resolution[9] = 0;
                char respart[5];
                strncpy(respart, resolution, 4);
                respart[4] = 0;
                x_respart = atoi(respart);
                strncpy(respart, resolution + 5, 5);
                y_respart = atoi(respart);

                write(fdout, resolution, 9);
                write(fdout, "\n", 1);

                mem[0] = '1';
            }
            else if (mem[0] == '4')
            {
                printf("Nepoddrzhana rezolucija");
                return 0;
            }
            else
            {
                sleep(1);
            }
        }
    }
    else
    {
        printf("Greshka pri povikuvanje na programata.\n");
        return 1;
    }

    return 0;
}