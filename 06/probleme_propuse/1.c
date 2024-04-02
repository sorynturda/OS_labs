#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid2, pid3, pid4, pid5;


    printf("P1: %d\n", getpid());
    pid2 = fork();
    if (!pid2) {
        printf("P2: %d\n", getpid());
        pid4 = fork();
        if (!pid4) {
            printf("P4: %d\n", getpid());
            sleep(60);
        } else
            wait(NULL);
    } else {
        pid3 = fork();
        if (!pid3) {
            printf("P3: %d\n", getpid());
            pid5 = fork();
            if (!pid5) {
                printf("P5: %d\n", getpid());
                sleep(60);
            } else
                wait(NULL);
        } else
            wait(NULL);
        wait(NULL);
    }
    return 0;
}