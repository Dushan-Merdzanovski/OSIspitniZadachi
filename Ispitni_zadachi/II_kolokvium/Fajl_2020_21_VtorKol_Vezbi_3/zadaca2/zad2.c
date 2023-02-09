#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

// 2014_2015_Operativni_sistemi_II_Kolokvium ovoj fajl e isto taka

/* 2. (30 поени) Да се овозможи pipe комуникација помеѓу два процеси. Едниот процес од тастатура
чита текст и преку pipe го испраќа до другиот процес. Другиот процес од pipe го чита текстот и
го запишува во меморија. Потоа, другиот процес чита текст од датотека „dat.txt“ и ги споредува
двата текстови дали се исти (текстот од pipe и текстот од датотеката). Резултатот од споредбата
го печати на екран.
Напомена: Забрането е користење на системските повици read/write */

int main() {
    int mypipe[2], fd;
    pipe(mypipe);
    pid_t dete;
    char text[100], newtext[100];
    int ekran = dup(1);

    dete = fork();

    if (dete == 0) {
        // dete proces
        if ((fd = open("dat.txt", O_RDONLY)) < 0) {
            printf("Neuspesno otvorena datoteka.\n");
        }

        close(mypipe[1]);
        dup2(mypipe[0], 0);
        scanf("%s", text);
        
        dup2(fd, 0);
        scanf("%s", newtext);

        printf("Noviot tekst:%s. vs Stariot tekst:%s.\n", newtext, text);

        if (strcmp(text, newtext) == 0) {
            printf("Tekstovite se isti\n");
        } else {
            printf("Tekstovite ne se isti.\n");
        }
    } else {
        // roditel
        printf("Vnesete tekst za prakjanje preku pipe\n");
        fflush(stdout);
        close(mypipe[0]);
        dup2(mypipe[1], 1);
        
        scanf("%s", text); // fgets(text, sizeof(text), stdin);
        printf("%s\n", text);
        fflush(stdout);
    }

    return 0;
}