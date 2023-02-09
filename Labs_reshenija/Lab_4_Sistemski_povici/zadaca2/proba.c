#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    char input[200];
    printf("Vnesi text:\n");
    gets(input);
    printf("%s",input);

    return 0;
}