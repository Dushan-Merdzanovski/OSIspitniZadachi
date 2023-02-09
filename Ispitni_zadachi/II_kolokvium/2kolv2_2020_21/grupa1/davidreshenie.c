#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
 
int main(int argc, char *argv[])
{
    int firstPipe[2];
    int secondPipe[2];
 
    int inputDup = dup(0);
    int outputDup = dup(1);
 
    if (pipe(firstPipe))
    {
        printf("First pipe failed!\n");
        return 1;
    }
 
    pid_t secondCommandChild = fork();
 
    if (secondCommandChild == 0)
    {
        if(pipe(secondPipe)) {
            printf("Second pipe failed!\n");
            return 1;
        }
 
        pid_t thirdCommandChild = fork();
 
        if(thirdCommandChild == 0) {
            // child of the child - third command
 
            close(secondPipe[1]);
 
            int averageGot = 0;
            int lastAverage = 0;
 
            dup2(secondPipe[0], 0);
 
            while(1) 
            {
                scanf("%d", &averageGot);
 
                printf("Third process: %d\n", averageGot - lastAverage);
                lastAverage = averageGot;
            }
        }
        else {
            // child - second command
 
            int countReceivedNumbers = 0;
            int average = 0;
            int numSum = 0;
 
            close(firstPipe[1]);
            close(secondPipe[0]);
 
            int numberGot;
            dup2(firstPipe[0], 0);
 
            while (1)
            {
                scanf("%d", &numberGot);
                countReceivedNumbers++;
                numSum += numberGot;
                average = numSum / countReceivedNumbers;
 
                dup2(secondPipe[1], 1);
                printf("%d\n", average);
                fflush(stdout);
 
                dup2(outputDup, 1);
                printf("Vtor proces (avg): %d\n", average);
                fflush(stdout);
            }
        }
    }
    else
    {
        // parent - first command
        close(firstPipe[0]);
 
        int inputNumber;
 
        while (1)
        {
            dup2(firstPipe[1], 1);
 
            scanf("%d", &inputNumber);
            printf("%d\n", inputNumber);
            fflush(stdout);
 
            dup2(outputDup, 1);
            printf("Prv proces chita: %d\n", inputNumber);
            fflush(stdout);
        }
    }
 
    return 0;
}