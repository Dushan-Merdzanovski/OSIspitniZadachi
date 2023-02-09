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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    char naredba[30];
    char argumenti[30];
    int deca[9];
    char pom[6];
    int d;
    char instanci;
    int inst;
    int id = atoi(argv[1]);
    key_t kluc = 1234;
    char *shm, *mm;
    int idshm = shmget(kluc, 1024, MAP_SHARED);
    shm = shmat(idshm, NULL, 0);
    
    int fd = open("dat.txt", O_RDWR);
    mm = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (id == 1)
    {
        // prv proces
        shm[0] = '0';
        while (1)
        {
            if (shm[0] != '0')
            {
                sleep(1);
            }
            else
            {
                printf("vnesi naredba");
                scanf("%s", naredba);
                printf("Dali ima argumenti");
                scanf("%d", &d);
                if (d)
                {
                    printf("vnesi gi argumentite");
                    scanf("%s", argumenti);
                }
                printf("vnesi broj na instanci od 1 do 9");
                scanf("%c", &instanci); // scanf("%d",&inst); instanci=itoa(inst);
                strcat(shm + 1, naredba);
                pom[0] = ' ';
                pom[1] = d ? '1' : '0';
                pom[2] = ' ';
                pom[3] = instanci; //
                pom[4] = ' ';      //
                pom[5] = 0;
                strcat(shm, pom); // 0ls 0 8 \0 // strcat(shm,instanci);
                if (d)
                {
                    strcpy(mm, argumenti);
                }
                shm[0] = '1';
            }
        }
    }
    else
    {
        // vtor proces
        while (1)
        {
            if (shm[0] != '1')
            {
                sleep(1);
            }
            else
            {
                char *p = shm + 1;
                int i = 0;
                while (*p != ' ')
                {
                    naredba[i] = *p;
                    i++;
                    p++;
                }
                d = *(p + 1) - '0';
                instanci = *(p + 3); // inst = atoi(p+3);
                int k = instanci - '0';
                for (i = 0; i < k; i++)
                {
                    deca[i] = fork();
                    if (deca[i] == 0)
                        break;
                }
                if (i < k)
                {
                    // dete proces
                    if (!d)
                    {
                        execlp(naredba, naredba, NULL);
                    }
                    else
                    {
                        execlp(naredba, naredba, mm, NULL);
                    }
                }
                else
                {
                    // roditel proces 2while(i){
                    wait(NULL);
                    i--;
                }
                shm[0] = '0';
            }
        }
    }
    return 0;
}
