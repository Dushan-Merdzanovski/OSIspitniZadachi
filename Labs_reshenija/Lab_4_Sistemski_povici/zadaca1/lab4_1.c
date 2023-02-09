#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#define SIZE 100
int main(int argc, char* argv[]) {
    char memorija[SIZE], name[20], nameletters[40], nameothers[40], c;
    int fdin, fdout_letters, fdout_others;
    ssize_t procitano;
    mode_t rezim = (S_IRWXU | S_IRWXG | S_IRWXO);
    if (argc != 2) {
        printf("Nepravilen povik, treba 1 argument\n");
        return 1;
    }
    if ((fdin = open(argv[1], O_RDONLY)) == -1) {
        printf("Ne mozam da ja otvoram %s za citanje\n", argv[1]);
        return 1;
    }
    strcpy(name, argv[1]);
    char *token = strtok(name, ".");
    strcpy(nameletters, token);
    strcpy(nameothers, token);
    strcat(nameletters, ".letters");
    strcat(nameothers, ".others");
    if ((fdout_letters = open(nameletters, O_WRONLY | O_CREAT, rezim)) == -1) {
        printf("Ne mozam da ja otvoram %s za zapisuvanje\n", nameletters);
        return 1;
    }

    if ((fdout_others = open(nameothers, O_WRONLY | O_CREAT, rezim)) == -1) {
        printf("Ne mozam da ja otvoram %s za zapisuvanje\n", nameothers);
        return 1;
    }
    char placeholder[2];
    placeholder[0] = ' ';
    placeholder[1] = '\0';
    char empty[2];
    empty[0] = ' ';
    empty[1] = '\0';
    int j = 0;
    while ((procitano = read(fdin, memorija, SIZE)) == SIZE || procitano > 0) {
        for (int i = 0; i < 100; i++) {
            placeholder[0] = memorija[i];
            /* strcpy(placeholder, memorija[i]); */
            if ((i+1) == procitano) {
                if (isalpha(memorija[i])) {
                    write(fdout_letters, placeholder, 1);
                } else {
                    write(fdout_others, placeholder, 1);
                }
                break;
            } else {
                if (isalpha(memorija[i])) {
                    write(fdout_letters, placeholder, 1);
                } else {
                    write(fdout_others, placeholder, 1);
                }
            }
        }
    }
    close(fdin);
    close(fdout_letters);
    close(fdout_others);
    if ((fdin = open(argv[1], O_RDWR)) == -1) {
        printf("Ne mozam da ja otvoram %s za zapisuvanje (i chitanje)\n", argv[1]);
        return 1;
    }
    // ova raboti super
    int i = 0;
    while (procitano = read(fdin, memorija, 1)) {
        lseek (fdin, i, SEEK_SET);
        write(fdin, empty, 1);
        i++;
    }
    close(fdin);
    return 0;
}


/* Задача 1: Да се напише програма во C која како аргумент од командна линија добива име
на влезна текстуална датотека. Програмата треба да ја измине влезната датотека и сите
букви да ги префрли во нова датотека со исто име како и влезната датотека само со
наставка „ letters“, додека пак останатите знаци ќе ги префрли во друга нова датотека со
исто име како и влезната, само со наставка „ others“. Изминувањето на датотеките се
прави така што се користат датотечни дескриптори, притоа, се зема по 100 знаци од
влезната додатотека и се распоредуваат во двете излезни датотеки соодветно. На крај,
содржината на влезната датотека треба да биде пребришана така што секој знак ќе се
замени со празно место. */
