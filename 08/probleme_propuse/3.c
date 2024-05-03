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

#define NR_THREADS 6

typedef struct {
    int id;
    sem_t *sem;
} TH_STRUCT;

void *thread_function(void *param) {
    TH_STRUCT *s = (TH_STRUCT*)param;
    while (1) {
        sem_wait(&s->sem[s->id]);
        printf("%d ", s->id + 1);
        fflush(stdout);
        sem_post(&s->sem[(s->id + 1) % NR_THREADS]);
    }
}

int main(int argc, char **argv)
{
    pthread_t tids[NR_THREADS];
    sem_t sem[NR_THREADS];
    TH_STRUCT params[NR_THREADS];

    if (sem_init(&sem[0], 0, 1) != 0) {
        perror("could not init the semaphore");
        return -1;
    }

    for (int i = 1; i < NR_THREADS; i++)
        if (sem_init(&sem[i], 0, 0) != 0) {
            perror("could not init the semaphore");
            return -1;
        }

    for (int i = 0; i < NR_THREADS; i++) {
        params[i].id = i;
        params[i].sem = sem;
        pthread_create(&tids[i], NULL, thread_function, &params[i]);
    }

    for (int i = 0; i < NR_THREADS; i++)
        pthread_join(tids[i], NULL);
    return 0;
}
