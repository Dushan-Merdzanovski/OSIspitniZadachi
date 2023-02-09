#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>

/*
2. Да се напише програма во C која работи со процеси и нитки. Главната програма (главната
нитка) како аргумент добива име на влезна датотека. Главната нитка треба да креира онолку
нитки колку што треба, така што, секоја нитка да добие по 10 линии од влезната датотека (нема
повеќе од 1000 линии, а притоа последната нитка може да добие и помалку од 10 линии).
Секоја една од нитките, ги изминува своите 10 линии од датотеката и брои колку има големи а
колку мали букви. Откако ќе завршат нитките, главната нитка печати на екран колку секоја
нитка нашла големи и мали букви и печати колку вкупно големи и мали букви биле
пронајдени. Не е дозволено содржината на целата датотека да биде прочитана во низа т.е.
секоја од нитките мора да работи со FILE * покажувач за изминување на датотеката т.е. на
линиите од датотеката.
*/

// 1000 / 10 -> 100

char dat[30];
#define number_max_threads 100; // broj na nitki ? aj 10 neka bidat
/* int from, to; */

typedef struct
{
    int id;
    int lower;
    int upper;
} p;

void *count_letters(void *id)
{
    p *thr = (p *)id;
    FILE *fptr;
    if ((fptr = fopen(dat, "r")) == NULL)
    {
        printf("File %s can't be opened.\n", dat);
        pthread_exit(NULL);
        exit(-1);
    }

    char c;
    int line = 0;
    while (line < (thr->id*10 - 1)) {
        c = fgetc(fptr);
        if(c == '\n')
            line++;
    } 

    while (line < thr->id*10 + 9)
    {
        c = fgetc(fptr);
        if (c == EOF) {
            break;
        }
        if (isalpha(c))
        {
            if (isupper(c))
            {
                thr->upper++;
            }
            else
            {
                thr->lower++;
            }
        } 
        if(c == '\n')
            line++;
    }
    fclose(fptr);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Nema dovolno argumenti!\n");
        return 0;
    }

    FILE *fptr;
    strcpy(dat, argv[1]);
    if ((fptr = fopen(dat, "r")) == NULL)
    {
        printf("File %s can't be opened.\n", dat);
        exit(-1);
    }

    char c;
    int lines;
    while ((c = fgetc(fptr)) != EOF)
    {
        if (c == '\n')
            lines++;
    }
    fclose(fptr);

    printf("IMAM %d LINII\n",lines);

    int num_threads = lines / 10;
    int last_thread = lines % 10;
    if (last_thread != 0)
    {
        num_threads++;
    }

    pthread_t threads[num_threads];
    p thr[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        thr[i].upper = 0;
        thr[i].lower = 0;
        thr[i].id = i;
        pthread_create(&threads[i], NULL, count_letters, (void *)&thr[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    int total_upper = 0;
    int total_lower = 0;
    for (int i = 0; i < num_threads; i++)
    {
        total_lower += thr[i].lower;
        total_upper += thr[i].upper;
    }

    for (int i = 0; i < num_threads; i++)
    {
        printf("Nitka %i pronajde %d lower i %d upper vo nejziniot del.\n", thr[i].id, thr[i].lower, thr[i].upper);
    }
    printf("\nVkupno: lower: %d upper: %d \n", total_lower, total_upper);

    return 0;
}