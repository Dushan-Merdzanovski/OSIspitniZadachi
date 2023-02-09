#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    pid_t dete; 

    if (argc < 2) {
        printf("Nedovolen broj na argumenti\n");
        return 0;
    }

    dete = fork();

    if (dete == 0) {
        printf("Jas sum dete proces i ke ja izvrsam naredbata %s %s\n",argv[1],argv[2]);
        execlp(argv[1],argv[1],argv[2],NULL);
        printf("Neuspesno se povika naredbata %s\n", argv[1]);
    } else {
        printf("Jas sum roditel proces i go chekam deteto.\n");
        if(waitpid(dete,NULL,WNOHANG) == dete) 
            printf("Deteto zavrshi.\n");
        else 
            printf("Deteto ne zavrshi ama im gonna go home.\n");

        printf("Deteto zavrshi\n");
    }

    return 0;
}