#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

// JUNI ZADACHA 3
// SO 5 KOMANDI ZADACHATA



void kreirajIme (char id, char *imedat) {
    char *tmp;
    sprintf(tmp, "%d", id);
    strcpy(imedat, tmp);
    /* strcpy(imedat, itoa(id)); */
    strcpy(imedat + strlen(imedat+1), ".txt");
}

int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    int z = argc - 2;

    int i;
    int id;
    char imedat[10]; // za da go kreira imeto na datotekata, so pid-ot na procesot
    pid_t deca[10]; // paralelno i seriski nachin
    pid_t dete; // seriski, ne moze vaka ustvari posho mora za sekoe dete da go chuva pid-ot
    pid_t novideca[10];
    
        // serisko izvrshuvanje
        for (i = 0; i < z; i++) {
            deca[i] = fork();
            if (deca[i] == 0)
                break;
            if (z < 5) {
                wait(NULL); // za seriski!
            }
        }
        if (i < z) {
            // dete proces seriski
            if (i == 0) {
                sleep(x);
            }

            id = getpid();
            kreirajIme(id, imedat);
            int fd = open(imedat, "w");
            if (fd < 0) {
                printf("Neuspeshno se otvori datotekata so ime %s",imedat);
                return 0;
            }
            dup2(fd, 1);
            execlp(argv[i+2], argv[i+2], NULL);
        } else {
            // roditel proces
            if ( z >= 5) {
                for (i = 0; i < z; i++) {
                    waitpid(deca[i], NULL, 0); // paralelno, gi ischekuva site deca da stignat
                }
            }

            for (i = 0; i < z; i++) {
                novideca[i] = fork();
                if (novideca[i] == 0) {
                    break;
                }        
            }
            if (i < z) {
                kreirajIme(deca[i], imedat);
                execlp("cat", "cat", imedat, NULL); // prikazhuva na ekran
            }
        }
        return 0;
    }

     void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  