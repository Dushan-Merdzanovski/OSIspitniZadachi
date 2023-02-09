#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main()
{
    char resolution[11];
    strncpy(resolution, "1080x1920\n", 10);
    resolution[9] = 0;
    char respart[5];
    strncpy(respart, resolution, 4);
    respart[4] = 0;
    int x_respart = atoi(respart);
    strncpy(respart, resolution + 5, 4);
    int y_respart = atoi(respart);

    printf("X: %d Y: %d\n", x_respart+1, y_respart);

    return 0;
}