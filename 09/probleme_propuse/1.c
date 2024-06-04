#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *v;

int n;

int *nrDiv;

pthread_mutex_t mutex_v;

pthread_mutex_t mutex_nrDiv;

void calculeazaDivizori(int i) {
    int contDiv = 0;
    for (int j = 1; j <= sqrt(v[i]); j++) {
        if (v[i] % j == 0) {
            if (j == v[i] / j) {
                contDiv++;
            } else {
                contDiv += 2;
            }
        }
    }

    pthread_mutex_lock(&mutex_nrDiv);
    nrDiv[i] = contDiv;
    pthread_mutex_unlock(&mutex_nrDiv);
}

void *thread_func(void *arg) {
    int i = (int)arg;

    while (i < n) {
        pthread_mutex_lock(&mutex_v);
        int aux = v[i];
        pthread_mutex_unlock(&mutex_v);

        calculeazaDivizori(i);

        i++;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilizare: ./program nr_thread-uri\n");
        return 1;
    }

    int t = atoi(argv[1]);

    scanf("%d", &n);
    v = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    nrDiv = malloc(n * sizeof(int));

    pthread_mutex_init(&mutex_v, NULL);
    pthread_mutex_init(&mutex_nrDiv, NULL);

    pthread_t thread_id[t];
    for (int i = 0; i < t; i++) {
        pthread_create(&thread_id[i], NULL, thread_func, (void *)i);
    }

    for (int i = 0; i < t; i++) {
        pthread_join(thread_id[i], NULL);
    }

    for (int i = 0; i < n; i++) {
        printf("%d: %d\n", v[i], nrDiv[i]);
    }

    free(v);
    free(nrDiv);

    pthread_mutex_destroy(&mutex_v);
    pthread_mutex_destroy(&mutex_nrDiv);

    return 0;
}
