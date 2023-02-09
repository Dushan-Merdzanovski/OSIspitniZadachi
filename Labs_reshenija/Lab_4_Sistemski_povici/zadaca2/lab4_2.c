#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* Задача 2: Да се напише програма во C програмскиот јазик која ќе ја изврши следнава
наредба напишана во SHELL.

Komanda1 | Komanda2 | Komanda3

Секоја команда ја извршува посебен процес, притоа како прв аргумент од командна линија
се праќа кој процес е (1, 2 или 3). Програмата се повикува 3 пати со различна вредност за
идентификација.
Komanda1: чита од тастатура текст и го запишува во pipe (завршува кога ќе внесе нул
терминатор)
Komanda2: чита од левиот pipe и копира во десниот pipe
Komanda3: чита од pipe, брои колку празни места има и печати на екран.
Напомена: да не се користат read/write за читање и запишување во pipes. */

int count_spaces(char *sentence) {
    int count = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] == ' ') {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    int whichcommand = atoi(argv[1]);
    if (whichcommand == 1) {
        // roditel - Command1
        int prvpipe[2], vtorpipe[2];
        int ekran = dup(1);

        if (pipe(prvpipe)) {
            printf("Ne moze da se vospostavi PrvPipe\n");
            return 0;
        }
    
        pid_t detekomanda2 = fork();
        if (detekomanda2 == 0) {

            if (pipe(vtorpipe)) {
                printf("Ne moze da se vospostavi VtorPipe od strana na Komanda2\n");
                return 0;
            }

            pid_t detekomanda3 = fork();
            if (detekomanda3 == 0) {
                // COMMAND 3
                close(prvpipe[0]);
                close(prvpipe[1]);
                close(vtorpipe[1]);

                dup2(vtorpipe[0], 0);
                dup2(ekran, 1);

                execlp(argv[0], argv[0], "3", NULL);
                printf("Ne se izvrshi exec na komanda3\n");
            } else {
                // COMMAND 2
                close(prvpipe[1]);
                close(vtorpipe[0]);

                dup2(prvpipe[0], 0);
                dup2(vtorpipe[1], 1);

                execlp(argv[0], argv[0], "2", NULL);
                dup2(ekran, 1);                
                printf("Ne se izvrshi execl na komanda2\n");
                return 0;
            }
        } else {
            // COMMAND 1
            close(prvpipe[0]);

            char text[200];
            printf("Vnesete text od tastatura(Komanda1):\n");
            gets(text);
            
            dup2(prvpipe[1], 1);
            printf("%s", text);
        }
    } else if (whichcommand == 2) {
        char text[200];
        gets(text);
        printf("%s", text);
    } else if (whichcommand == 3) {
        char text[200];
        gets(text);
        int numspaces = count_spaces(text);
        printf("Komanda3: Vo tekstot ima %d prazni mesta.\n", numspaces);
        return 0;
    }            
    return 0;       
}