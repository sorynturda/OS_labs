#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int n;
	int id;
	pthread_mutex_t *lock;
} TH_STRUCT;

int res;


void *thread_function(void *param) {
	TH_STRUCT *s = (TH_STRUCT *)param;
	int fd = -1;
	char path[30];
	sprintf(path, "./%d.txt", s->id);
	fd = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1) {
		perror("could not create the output file");
		return NULL;
	}
	char buff = 's';
	for (int i = 0; i < s->n; i++)
		write(fd, &buff, 1);
	close(fd);
	pthread_mutex_lock(s->lock);

	res++;
	pthread_mutex_unlock(s->lock);
	return NULL;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage %s numbers\n", argv[0]);
		return 1;
	}
	int nr_threads = argc - 1;
	int a[nr_threads];
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	TH_STRUCT params[nr_threads];
	pthread_t tids[nr_threads];
	for (int i = 0; i < nr_threads; i++)
		a[i] = atoi(argv[i + 1]);
	for (int i = 0; i < nr_threads; i++) {
		params[i].n = a[i];
		params[i].id = i + 1;
		params[i].lock = &lock;
		if (pthread_create(&tids[i], NULL, thread_function, &params[i]) != 0) {
			perror("could not create the thread");
			return 2;
		}
	}
	for (int i = 0; i < nr_threads; i++) {
		if (pthread_join(tids[i], NULL) != 0) {
			perror("could not join the thread");
			return 3;
		}
	}
	pthread_mutex_destroy(&lock);
	printf("Numarul de fisiere create este %d\n", res);
	return 0;
}
