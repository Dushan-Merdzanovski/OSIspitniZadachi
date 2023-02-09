#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int countSpaces(char*);

int main(int argc, char *argv[])
{
    int firstPipe[2];
    int secondPipe[2];

    if(pipe(firstPipe)) {
        printf("First pipe failed!\n");
        return 1;
    }

    pid_t secondCommandChild = fork();

    if(secondCommandChild == 0) {

        if(pipe(secondPipe)) {
            printf("Second pipe failed!\n");
            return 1;
        }

        pid_t thirdCommandChild = fork();

        if(thirdCommandChild == 0) {
            // child child - third command
            char finalReceive[255];

            dup2(secondPipe[0], 0);
            gets(finalReceive);

            // printf("%s\n", finalReceive);

            int totalSpaces = countSpaces(finalReceive);
            printf("%d\n", totalSpaces);
        }
        else {
            // child - second command
            char receivedInput[255];

            dup2(firstPipe[0], 0);
            gets(receivedInput);

            dup2(secondPipe[1], 1);
            printf("%s\n", receivedInput);
        }
    }
    else {
        // parent - first command
        char input[255];

        printf("Vnesete text od tastatura(Komanda1):\n");
        gets(input);

        dup2(firstPipe[1], 1);
        printf("%s\n", input);
    }
    
    return 0;
}

int countSpaces(char *str)
{
    int countSpaces = 0;

    for(int i = 0; i < strlen(str); i++) {

        if(isspace(str[i])) {
            countSpaces++;
        }
    }
    return countSpaces;
}
