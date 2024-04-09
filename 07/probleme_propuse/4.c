#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define NR_THREADS 9


void *th_func(void *param) {
    int *tid = (int *) param;
    for (;;) {
        sleep(rand() % 4 + 1);
        printf("thread_id: %d\n", *tid);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t tid[NR_THREADS];
    int params[NR_THREADS];
    for (int i = 0; i < NR_THREADS; i++) {
        params[i] = i + 1;
        pthread_create(&tid[i], NULL, th_func, &params[i]);
    }
    int th_running = 9, n;
    while (th_running > 0 && scanf("%d", &n) == 1)
        if (n > 0 && n < 10) {
            pthread_cancel(tid[n-1]);
            th_running--;
        }

    return 0;
}
