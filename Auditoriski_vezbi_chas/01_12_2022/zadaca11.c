#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    key_t kluc = 1234; // random kluc
    int id;
    id = shmget(kluc, 1024, 0644 | IPC_CREAT); // 666 vs 777 r w i x; 2 e r; 4 e w; 1 e execute; 6 e rw (2+4); 7 = 2+4+1 -> rwx
    char *mem;                                  //

    if (id < 0)
    { // == -1
        printf("Neuspeshno dobivanje pristap do memorijata.  \n");
        return 0;
    }

    // shmat(id,NULL,0); // vrakja void* pointr. NULL od pochetok na memorijata
    //  moze i vaka
    mem = shmat(id, mem, 0); // ovoj se prenasochuva u drugata , toa sho go zboreshe goki

    if (mem == (void*)-1) // == NULL
    {
        printf("Neuspesno prikacuvanje na memorijata\n");
        return 0;
    }

    printf("%s", mem);
    shmdt(mem); // detatch
    shmctl(id, IPC_RMID, 0);

    return 0;
}