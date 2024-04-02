#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    if(argc != 4){
        perror("error");
        exit(-1);
    }
    int x, y;
    sscanf(argv[1], "%d", &x);
    sscanf(argv[2], "%d", &y);
    if(argv[3][0] == '-')
        exit(x-y);
    exit(y+x);
    return 0;
}