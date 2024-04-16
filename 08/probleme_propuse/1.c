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

void *thread_function(void *p)
{
    sem_t *sem = (sem_t *)p;
    int i;
    long aux;
    for (i = 0; i < M; i++) {
        sem_wait(sem);
        aux = count;
        aux++;
        usleep(random() % 10);
        count = aux;
        sem_post(sem);
    }
    return NULL;
}

int main(void)
{
    sem_t sem;
    pthread_t tids[NR_THREADS];
    int i;
    srand(time(NULL));

    if (sem_init(&sem, 0, 1) != 0) {
        perror("could not init the semaphore");
        return -1;
    }

    for (int i = 0; i < NR_THREADS; i++)
        pthread_create(&tids[i], NULL, thread_function, &sem);

    for (int i = 0; i < NR_THREADS; i++)
        pthread_join(tids[i], NULL);
    sem_destroy(&sem);
    printf("%ld\n", count);
    return 0;
}
