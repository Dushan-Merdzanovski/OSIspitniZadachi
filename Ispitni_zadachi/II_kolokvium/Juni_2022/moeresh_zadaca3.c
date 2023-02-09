#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void create_name(int id, char *datname) {
    char *tmp;
    sprintf(tmp, "%d", id);
    strcpy(datname, tmp);
    strcat(datname, ".txt");
}

int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    int ekran = dup(1);
    int z = argc - 2;
    pid_t deca[10];
    pid_t novideca[10];
    char dat_name[15];
    int i;
    mode_t rezim = (S_IRWXU | S_IRWXG | S_IRWXO);

    for (i = 0; i < z; i++) {
        deca[i] = fork();
        if (deca[i] == 0)
            break;
        if (z < 5) {
            wait(NULL); // seriski
        }
    }

    if (i < z) {
        // decata 
        if ((z >= 5) || (i == 0)) {
            sleep(x);
        }
        int id = getpid();
        create_name(id, dat_name);
        int fd;
        if ((fd = open(dat_name, O_WRONLY | O_CREAT, rezim)) == -1) {
            printf("Ne mozam da ja otvoram %s za zapishuvanje\n", dat_name);
            return 1;
        }
        printf("%s\n", dat_name);
        dup2(fd, 1);
        execlp(argv[i + 2], argv[i + 2], NULL);
        write(ekran, "Ne se izvrshi komandata\n", 25);
    } else {
        // roditel
        if (z >= 5) {
            waitpid(deca[i], NULL, 0);
        }

        for (i = 0; i < z; i++) {
            novideca[i] = fork();
            if (novideca[i] == 0) 
                break;
        }

        if (i < z) {
            create_name(deca[i], dat_name);
            printf("%s novideca", dat_name);
            execlp("cat", "cat", dat_name, NULL);
            printf("Ne se izvrshi komandata\n");
        }

        for (int i = 0; i < z; i++) {
            wait(NULL);
        }
    }

    return 0;
}