#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
/* 1.
Да се напише програма во C програмскиот јазик за комуникација помеѓу два процеси. Програмата како
аргумент добива име на датотека преку која ќе комуницираат двата процеси преку метод на мемориско
мапирање. Родител процесот креира дете процес на кого му го кажува името на датотеката преку која ќе
комуницираат. Датотеката е организирана така што, најпрво има 1 бајт за синхронизација, 128 бајти за
клуч и 1KB меморија. Иницијално меморијата од 1KB е кодирана. Родител процесот, од датотека
+kluc.out“ го чита клучот со кој треба да ја декодира меморијата. Дете процесот има 3 обиди да ја
отклучи меморијата, притоа го чита клучот за отклучување од тастатура и го запишува во меморијата, и
му сигнализира на родител процесот да ја отклучи меморијата. Родител процесот на секоја една секунда
проверува дали треба да ја отклучи меморијата. Доколку треба да ја дешифрира меморијата, го чита
клучот и го праќа на функцијата otkluci(char *kluc, char *tekst, int p); каде што даден текст го шифрира
или дешифрира врз основа на вредноста на +p“ (0 шифрира, 1 дешифрира). Доколку го дешифрира, му
кажува на дете процесот дека е дешифриран текстот и го држи дешифриран 10 секунди. По 10 секунди,
повторно го шифрира текстот.*/

void otkluci(char *kluc, char *tekst, int p)
{
    int k = strlen(kluc);
    int t = strlen(tekst);
    int i, sum, z = 0;
    for (i = 0; i < t; i++)
    {
        if (p == 0)
        {
            sum = kluc[z] + tekst[i];
            if (sum > 255)
            {
                sum -= 255;
            }
        }
        else
        {
            sum = kluc[z] - tekst[i];
            if (sum < 0)
            {
                sum += 255;
            }
        }
        tekst[i] = sum;
        i++;
        z++;
        if (z == k)
            z = 0;
    }
}

int main(int argc, char *argv[])
{
    int fd, kluc, obidi;
    char key[128], *mem, unlock[128];
    pid_t dete;
    if (argc < 2)
    {
        printf("nepravilen povik");
        return 0;
    }
    dete = fork();
    fd = open(argv[1], O_RDWR);
    mem = mmap(NULL, 1 + 128 + 1024, PROT_READ, MAP_SHARED, fd, 0);
    if (dete > 0)
    {
        // roditel
        kluc = open("kluc.out", O_RDONLY);
        read(kluc, key, 128);
        mem[0] = '0';
        while (1)
        {
            while (mem[0] == '0')
            {
                sleep(1);
            }
            if (strcmp(key, mem + 1) == 0)
            {
                otkluci(key, mem + 1 + 128, 1);
                mem[0] = '2';
                sleep(10);
                otkluci(key, mem + 1 + 128, 0);
                mem[0] = '0';
            }
            else
            {
                mem[0] = '0';
            }
        }
    }
    else
    {
        // dete proces
        obidi = 0;
        while (obidi < 3)
        {
            scanf("%s", unlock);
            strcpy(mem + 1, unlock);
            mem[0] = '1';
            while (mem[0] == '1')
            {
                sleep(1);
            }
            if (mem[0] == '2')
            {
                printf("Uspeshno otkluceno\n %s\n", mem + 1 + 128);
                break;
            }
            else
            {
                obidi++;
            }
        }
    }
    return 0;
}