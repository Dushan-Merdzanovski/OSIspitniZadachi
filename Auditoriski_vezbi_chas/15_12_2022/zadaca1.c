#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAXD 10
#define SIZE 512

// sistemski povici primer 1
/*
• Да се напише програма користејќи системски повици и датотечни дескриптори
за копирање на датотека. Програмата треба да се користи на следниов начин:
• Првиот аргумент од командна линија е името на датотеката што треба да се
копира
• Сите останати N - 2 аргументи се имињата на новите датотеки што треба да се
креираат
*/

int main(int argc, char *argv[])
{
    int test, i;
    char memorija[SIZE];
    ssize_t procitano;
    int deskriptori[MAXD];
    mode_t rezim = (S_IRWXU | S_IRWXG | S_IRWXO);
    if (argc < 3)
    {
        printf("Nepravilen povik: minimum 2 datoteki\n");
        return (1);
    }

    if ((argc - 2) > MAXD)
    {
        printf("Nadminat e maksimalniot broj od %d datoteki\n", MAXD);
        return (1);
    }

    if ((deskriptori[1] = open(argv[1], O_RDONLY)) == -1)
    {
        printf("nemozam da ja otvoram %s za citanje\n", argv[1]);
        return (1);
    }

    for (i = 2; i < argc; i++)
    {
        if ((deskriptori[i] = open(argv[i], O_WRONLY | O_CREAT, rezim)) == -1)
        {
            printf("Datotekata %s nemozam da ja kreiram \n", argv[i]);
        }
    }

    while ((procitano = read(deskriptori[1], memorija, SIZE)) == SIZE) // imalo ili 512 ili poishe Bytes vo datotekata
    {
        for (i = 2; i < argc; i++)
            write(deskriptori[i], memorija, SIZE);
    }

    for (i = 2; i < argc; i++)
        write(deskriptori[i], memorija, procitano); // da go dokopirame toa shto ostanalo, ako ima neshto ostanato fo

    for (i = 1; i < argc; i++)
        close(deskriptori[i]);
    return 0;
}
