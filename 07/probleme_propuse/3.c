#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


void *th_func(void *param) {
    sleep(60);
    return NULL;
}

int main() {
    pthread_t tid;
    int cnt = 0;
    while (pthread_create(&tid, NULL, th_func, NULL) == 0)
        cnt++;
    printf("s-au creat %d fire de executie\n", cnt);
    return 0;
}

