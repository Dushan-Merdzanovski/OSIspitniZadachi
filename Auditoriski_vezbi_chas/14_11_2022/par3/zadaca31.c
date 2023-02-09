#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int K;
    int i;
    char naredba[30], a1[30], a2[30], a3[30];
    pid_t deca[20]; // ovie sami si gi davame brojkive kolku da se

    printf("Vnesi go K\n");
    scanf("%d", &K);

    for (i = 0; i < K; i++)
    {
        printf("Vnesi naredba so tri argumenti za deteto %d\n", i);
        scanf("%s %s %s %s", naredba, a1, a2, a3);
        deca[i] = fork();
        if (deca[i] == 0)
            break;
    }

    if (i < K)
    { // dete proces
        int cekaj = rand() % 20 + 1;
        printf("Dete %d ke ceka %d sekundi", i, cekaj);
        sleep(cekaj);
        execlp(naredba, naredba, a1, a2, a3, NULL);
        printf("Neuspesen povik na exec na deteto %d", i);
    }
    else
    {
        int sekundi = 0;
        int procesi[K];
        for (i = 0; i < K; i++)
        {
            procesi[i] = -1;
        }

        while (1)
        {
            for (i = 0; i < K; i++)
            {
                procesi[i] = waitpid(deca[i], NULL, WNOHANG); // moze i waitpid seedno ne prai niso2
                // vrakja 0 ako detevo ne zarvsilo, ili pid na deteto ako zavrshilo
            }

            for (i = 0; i < K; i++)
            {
                if (procesi[i] == -1) // dali barem eden od niv e so -1, togash vrednosta na i ke bide pomala od K
                    break;
            }
            if (i == K)
                break;

            sleep(1);
            sekundi++;
            // ova sve meh raboti, on go objasnuvashe probaj da skontash neso crtashe
        }
        printf("Zavrsuva i roditel procesot\n");
    }
    // bonus ima doreshen e
    return 0;
}