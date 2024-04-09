#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NR_THREADS 6

typedef struct {
    int pos;
    int n;
} TH_STRUCT;

void *count_ones(void *param) {
    TH_STRUCT *s = (TH_STRUCT*)param;
    int cnt = 0;
    for (int i = s->pos; i <= s->n; i += NR_THREADS) {
        int number = i;
        while (number) {
            if (number % 10 == 1)
                cnt++;
            number /= 10;
        }
    }
    return (void*)(long)cnt;
}

int main(int argc, char **argv) {
    if(argc != 2){
        fprintf(stderr, "Enter a number\n");
        exit(-1);
    }

    int n;
    sscanf(argv[1], "%d", &n);

    pthread_t tid[NR_THREADS];
    TH_STRUCT params[NR_THREADS];
    void *result;
    int cnt = 0, th_cnt;
    for (int i = 0; i < NR_THREADS; i++) {
        params[i].pos = i + 1;
        params[i].n = n;
        pthread_create(&tid[i], NULL, count_ones, &params[i]);
    }

    for (int i = 0; i < NR_THREADS; i++) {
        pthread_join(tid[i], &result);
        th_cnt = (int)(long)result;
        cnt += th_cnt;
    }
    printf("Sunt %d de 1 in numerele de la 1 la %d\n", cnt, n);
    return 0;
}
