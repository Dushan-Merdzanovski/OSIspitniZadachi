/*Да се напише програма која како аргумент добива команда која
треба да ја изврши.
• Програмата треба да изврши замена на стандардниот знак „&“
со „%“ за започнување на програма како позадински или преден
процес*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t dete;
    pid_t tatko;
    int chekaj = 1;
    if (argv[argc - 1][strlen(argv[argc - 1]) - 1] == '%')
    {
        chekaj = 0;
        argv[argc - 1][strlen(argv[argc - 1]) - 1] = '\0';
    }
    else if (argv[argc - 1][0] == '%')
    {
        chekaj = 0;
        argv[argc - 1][0] = '\0';
    }
    dete = fork();
    if (dete == 0)
    { // dete_proces
        execvp(argv[1], &argv[1]);
        printf("Ne uspea povikot\n");
    }
    else
    { // tatko proces
        if (chekaj)
        {
            waitpid(dete, NULL, '\0');
            printf("dochekav dete\n");
        }   
        else
            printf("Ne chekam\n");
    }
    return 0;
}