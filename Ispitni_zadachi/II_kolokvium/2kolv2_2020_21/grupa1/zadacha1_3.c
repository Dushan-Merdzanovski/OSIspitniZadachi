#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define READ_MEM_SIZE 100

int main(int argc, char *argv[]) {
    int key = atoi(argv[1]);
    char name_dat[10], tmp[5];
    char *memory;
    char memory_array[100];
    int id, i, bytes_read;
    char c;
    int length_memory;
    int number_digits = 0;

    strcpy(name_dat, argv[2]);
    id = shmget(key, READ_MEM_SIZE + 5, 0644 | IPC_CREAT); // 100B + 1B sync + 4B size
    if(id == -1) {
        printf("neuspesno dobivanje pristap");
    }
    memory = shmat(id, NULL, 0);

    while(1) {
        if (memory[0] == '1' || memory[0] == '2') {
            memory[0] = '0';
            strncpy(tmp, memory + 1, 4);
            tmp[4] = 0;
            length_memory = atoi(tmp);
            for (int i = 0; i < READ_MEM_SIZE && i < length_memory; i++) {
                if (isdigit(memory[i + 5])) {
                    number_digits++;
                }
            }
            int tempint = memory[0] - '0';
            tempint++;
            memory[0] = tempint + '0';
            if (length_memory < READ_MEM_SIZE)
                break;
        } else {
            sleep(1);
        }
    }

    printf("Pronajdeni se %d cifri!\n", number_digits);

    return 0;
}