#include <stdio.h>   /* стандардни I/O функции */
#include <pthread.h> /* за работа со PTHREAD нитки */

void *do_loop(void *data)
{
    int i;
    int j;
    int me = *((int *)data); /* реден број на нитката, не е TID*/
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 500000; j++); /* донесување одредено доцнење*/
        printf("'%d' - Got '%d'\n", me, i);
    }
    /* успешно завршување на нитката */
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int thr_id;         /* reden broj na nitkata*/
    pthread_t p_thread; /* struktura na nitkata */
    int a = 1;          /* poraka do nitka 1 */
    int b = 2;          /* poraka do nitka 2 */
    thr_id = pthread_create(&p_thread, NULL, do_loop, (void *)&a);
    do_loop((void *)&b);

    return 0;
}