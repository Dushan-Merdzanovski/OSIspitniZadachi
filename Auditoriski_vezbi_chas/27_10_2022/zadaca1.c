#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t dete;

    if (argc < 2)
    {
        printf("Nedovolen broj na argumenti\n");
        return 0;
    }

    dete = fork();

    if (dete == 0)
    {
        // dete procesot
        printf("Jas sum dete proces i ke ja izvrsam naredbata %s ", argv[1]);
        execlp(argv[1], argv[1], NULL);
        printf("Neuspesno se povika naredbata %s\n", argv[1]); // nema da se ispechati ako e uspesno izvrsena execlp(), taa go zamenuva cel kod blablabla
    }
    else
    {
        printf("Ja sum roditel proces i go chekam deteto\n");
        // wait(NULL); // go chekame deteto bezuslovno
        if (waitpid(dete, NULL, WNOHANG) == dete) // go proveruva statusot, vrakja 0 ako ushte ne e zavrseno deteto. wnohang samo dali zavrsilo deteto
        {
            printf("Deteto zavrsi\n");
        }
        else
        {
            printf("Deteto ne zavrsi ama ja ke si idam doma\n");
        }
        printf("Deteto zavrshi\n");
    }
    // u terminal ./zadaca1.c ls za prviot del od zadachata
    // gedit & go startuva ko nezavisen proces, ne go cheka vo terminal,
    // moze u prodolzenie da izvrsuvame naredbi u terminal
    // ./zadaca2 gedit

    // naredba waitpid(dete,NULL,WNOHANG);
    return 0;
}