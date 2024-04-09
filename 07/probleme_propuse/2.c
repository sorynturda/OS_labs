#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_THREADS 15

typedef struct {
    int pos;
    int n;
    int NR_THREADS;
} TH_STRUCT;

void *count_ones(void *param) {
    TH_STRUCT *s = (TH_STRUCT*)param;
    int cnt = 0;
    for (int i = s->pos; i <= s->n; i += s->NR_THREADS) {
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
    if (argc != 2) {
        fprintf(stderr, "Enter a number\n");
        exit(-1);
    }
    clock_t begin, end;
    double time_spent;
    int n;
    sscanf(argv[1], "%d", &n);
    char file_name[512];
    snprintf(file_name, 512, "./out/%d.txt", n);
    int fd = creat(file_name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Could not open the output file");
        close(fd);
        return 1;
    }
    pthread_t tid[MAX_THREADS];
    TH_STRUCT params[MAX_THREADS];
    void *result;


    for (int NR_THREADS = 1; NR_THREADS < MAX_THREADS; NR_THREADS++) {
        int cnt = 0, th_cnt;
        char buff[100];

        begin = clock();

        for (int i = 0; i < NR_THREADS; i++) {
            params[i].pos = i + 1;
            params[i].n = n;
            params[i].NR_THREADS = NR_THREADS;
            pthread_create(&tid[i], NULL, count_ones, &params[i]);
        }

        for (int i = 0; i < NR_THREADS; i++) {
            pthread_join(tid[i], &result);
            th_cnt = (int)(long)result;
            cnt += th_cnt;
        }
        
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        snprintf(buff, 100, "THREADS: %d\n time_spent: %lf\n\n", NR_THREADS, time_spent);
        write(fd, &buff, 100);
    }
    close(fd);
    return 0;
}

