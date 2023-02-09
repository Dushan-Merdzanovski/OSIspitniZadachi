#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Задача 4
Да се напише С програма за кодирање на дадена слика од страна на „N“ нитки. Секоја нитка, како
аргументи добива: <koj_del_od_slikata_go_kodira> < kolku pikseli ima toj del>. Сликата е запишана
во текстуална датотека, така што секој знак е пиксел кој има код на боја од 0 до 255. Секоја нитка
паралелно врши кодирање на сликата, притоа секоја си знае кој дел е нејзин и колкаво парче (ги
добива горните леви координати на подматрицата која треба да ја кодира и димензијата на
подматрицата). Кодирањето се прави така што се зема пиксел по пиксел и се проверува дали
неговите соседни пиксели (околу него во подматрицата) имаат иста вредност или се разликуваат
најмногу за 1. Доколку е тој услов исполнет, тогаш на екран процесот ги печати координатите на
пикселот и бојата со која се кодира. Доколку не е исполнет условот, на екран не се печати ништо.
Сликата е со димензии 1096х1080. Главната нитка ја пополнува матрицата од датотеката и ги
започнува останатите нитки. Бројот на нитки со кои се кодира се внесува како аргумент од
командна линија, додека пак, податоците што се праќаат на секоја нитка (како аргументи) се
внесуваат од тастатура од главната нитка. */


#define max_rows 1096
#define max_cols 1080
#define num_threads 8
int mat[max_rows][max_cols];
typedef struct {
    int x, y, lx, ly;
}threadstruct;

void *kodiraj(void* id) {


    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_t threads[num_threads];
    FILE *fptr;

    if(!(fptr = fopen("file.txt","r"))) {
        printf("Can't open file\n");
        return -1;
    }
    char c;
    while (c = fgetc(fptr) != EOF) {
        for (int i =0; i < max_cols; i++) {
            for(int j = 0; j < max_cols; j++) {
                mat[i][j] = c;
            }
        }
    }

    threadstruct thr[num_threads];

    for (int i = 0; i<num_threads;i++) {
        for (int j = 0; j<num_threads; j++){
            thr[i].x = i*max_rows/num_threads;
            thr[i].y = i*max_cols/num_threads;
            thr[i].lx = max_rows/num_threads;
            thr[i].ly = max_cols/num_threads;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i],NULL,kodiraj,(void*)&thr[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i],NULL);
    }
    


    return 0;
}