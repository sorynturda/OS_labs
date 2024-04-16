#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define NR_THREADS 4
#define M 1000

long count;

void *thread_function(void *unused)
{
    int i;
    long aux;
    for (i = 0; i < M; i++) {
        aux = count;
        aux++;
        usleep(random() % 10);
        count = aux;
    }
    return NULL;
}

int main(void)
{
    pthread_t tids[NR_THREADS];
    int i;

    srand(time(NULL));

    for(int i=0;i<NR_THREADS;i++)
        pthread_create(&tids[i], NULL, thread_function, NULL);
    for(int i=0;i<NR_THREADS;i++)
        pthread_join(tids[i], NULL);
    printf("%ld\n", count);
    return 0;
}
