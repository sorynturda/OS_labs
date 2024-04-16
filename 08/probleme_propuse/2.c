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

#define NR_THREADS 16

int nrThreads;
sem_t sem2;
void *limited_area(void *p)
{
    sem_t *sem = (sem_t *)p;
    sem_wait(sem);

    sem_wait(&sem2);
    nrThreads++;
    sem_post(&sem2);

    usleep(1000);
    printf("The number of threads in the limited area is: %d\n", nrThreads);

    sem_wait(&sem2);
    nrThreads--;
    sem_post(&sem2);

    sem_post(sem);
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return -1;
    }
    int n;
    sscanf(argv[1], "%d", &n);
    sem_t sem;
    pthread_t tids[NR_THREADS];
    int i;
    srand(time(NULL));

    if (sem_init(&sem, 0, n) != 0) {
        perror("could not init the semaphore");
        return -1;
    }
    if (sem_init(&sem2, 0, 1) != 0) {
        perror("could not init the semaphore");
        return -1;
    }
    for (int i = 0; i < NR_THREADS; i++)
        pthread_create(&tids[i], NULL, limited_area, &sem);

    for (int i = 0; i < NR_THREADS; i++)
        pthread_join(tids[i], NULL);
    sem_destroy(&sem);
    return 0;
}
