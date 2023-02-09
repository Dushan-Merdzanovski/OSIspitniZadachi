#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int seg_id;
    char *sharred;
    key_t kluc = 1234;
    // se obiduva da alocira memorija so kluc 1234, so golemina 27 bajti i istata da ima privilegii za citanje i zapisuvanje t.e. 0666
    if ((seg_id = shmget(kluc, 27, IPC_CREAT | 0666)) < 0)
    {
        printf("nemozam da alociram");
        return 0;
    }
    // se obiduva da ja prikaci taa memorija vo soodvetniot adresen proctor na procesot, pritoa posledniot argument kazuva deka taa memorija kje bide shared
    if ((sharred = shmat(seg_id, NULL, 0)) == (char *)-1)
    {
        printf("Nemozam da pristapam");
        return 0;
    }

    while (1)
    {
        // vo bezkonecen ciklus vrshi sinhronizacija na pristap preku prviot bajt vo memorijata
        // Dokolku prviot bajt e 0, togas toa znaci deka nikj ne ja koristi memorijata
        if (sharred[0] != 'l') // l za locked
        {
            sharred[0] = 'l';
            strcpy(&sharred[1], argv[1]);
            sharred[7 + 1] = 0;
            printf("zaklucuvam\n");
            sleep(10);
            sharred[0] = 'u';
            printf("otklucuvam\n");
            break;
        }
        else
        {
            printf("cekam\n");
            sleep(1);
        }
    } // while(1)
    // shmdt(sharred);
    // sleep(10);
    //  shmctl treba da ja povika samo posledniot process, toj koj sto planira da ja unisti taa memorija i nikojpat povekje da ne se koristi.
    // shmctl(seg_id,IPC_RMID,0);
    return 0;
}