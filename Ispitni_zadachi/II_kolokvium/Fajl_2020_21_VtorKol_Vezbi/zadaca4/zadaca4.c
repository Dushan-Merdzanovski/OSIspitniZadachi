#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Zadaca4) Да се напише програма во С која што ќе комуницира со дете процес преку две pipe комуникациски
    точки.Првата комуникациска точка е од насока од родителот кон детето,
    а втората обратно.Родител процесот, од тастатура, чита одредена низа од знаци и истата ја праќа до дете процесот,
    притоа му сигнализира дека има податоци во едниот pipe.Дете процесот, треба да ја земе низата од знаци,
    да изброи колку последователно има букви(десно од тековната има буква) и кога ќе заврши со проверката,
    печати на екран и му кажува на родител процесот преку вториот pipe
    дека може да прати податоци преку првиот pipe.Читањето од цевката и
    запишувањето во истата да се прави со printf и scanf. */

int main()
{
    int pipe1[2], pipe2[2], brojac = 0;
    char c;
    int kopija;
    pid_t dete;
    char memorija[512], *p;
    pipe(pipe1);
    pipe(pipe2);
    dete = fork();
    if (dete == 0)
    { // dete
        // dup2(1, kopija); // ovde e ekran, STDOUT
        kopija = dup(1);
        close(pipe1[1]);
        close(pipe2[0]);
        dup2(pipe1[0], 0);
        

        while (1)
        {
            scanf("%c", &c);
            if (c == '0')
            {
                sleep(1);
            }
            else
            {
                dup2(pipe2[1], 1);
                printf("0\n"); // nema poraka, nema shto da prochita, t.e. lock
                fflush(stdout);
                brojac = 0;
                scanf("%s", memorija);
                p = memorija;
                while (*p)
                {
                    if (isalpha(*p) && isalpha(*(p + 1)))
                    {
                        brojac++;
                    }
                    p++;
                }
                char tmp[10];
                /* sprintf(tmp, "%d", brojac); */
                dup2(kopija, 1);
                printf("Imalo %d posledovatelni bukvi mesta.\n", brojac + 1);
                dup2(pipe2[1], 1);
                printf("1\n");
                fflush(stdout);
            }
        }
    }
    else
    {
        kopija = dup(0); // roditel
        // dup2(0, kopija); // ovde e tastatura, STDIN
        close(pipe1[0]);
        close(pipe2[1]);
        dup2(pipe1[1], 1);
        dup2(pipe2[0], 0);
        printf("0\n");
        fflush(stdout);
        read(kopija, memorija, 100);
        printf("1\n");
        fflush(stdout);
        printf("%s\n", memorija);

        while (1)
        {
            scanf("%c", &c);
            if (c == '0')
            {
                sleep(1);
            }
            else
            {
                printf("0\n");
                fflush(stdout);
                read(kopija, memorija, 100);
                printf("1\n");
                fflush(stdout);
                printf("%s\n", memorija);
                fflush(stdout);
            }
        }
    }
    return 0;
}