#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>

DIR *dir = NULL;


int main(int argc, char **argv) {
	pid_t pid2, pid3, pid4, pid5;
	int fd[2];
	printf("P1: %d\n", getpid());
	if (pipe(fd) != 0) {
		perror("could not create the pipe");
		return 1;
	}
	pid2 = fork();

	if (pid2 == 0) {
		close(fd[1]);
		printf("P2: %d\n", getpid());
		char buff;
		int ok = 1;
		for (;;) {
			if (ok) {
				printf("P2: ");
				ok = 0;
			}
			read(fd[0], &buff, 1);
			if (buff == '\n')ok = 1;
			if (buff == -1)
				break;
			printf("%c", buff);

		}
		printf("\n");
		close(fd[0]);
	}
	else {
		pid3 = fork();
		if (pid3 == 0) {
			printf("P3: %d\n", getpid());
			pid4 = fork();
			if (pid4 == 0) {
				printf("P4: %d\n", getpid());

			}
			else {
				pid5 = fork();
				if (pid5 == 0) {
					close(fd[0]);
					printf("P5: %d\n", getpid());
					dir = opendir("./");
					//char path[250];
					char end = '\n';
					struct dirent *entry;
					struct stat statbuf;
					while ((entry = readdir(dir)) != NULL) {
						if (lstat(entry->d_name, &statbuf) == 0 && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
							//printf("P5: %s\n", entry->d_name);
							for (int i = 0; entry->d_name[i]; i++)
								write(fd[1], &entry->d_name[i], 1);

							write(fd[1], &end, 1);
						}

					}
					closedir(dir);
					end = -1;
					write(fd[1], &end, 1);
					close(fd[1]);

				}
				else {
					wait(NULL);
				}
				wait(NULL);
			}
		}
		else {
			wait(NULL);
		}
		wait(NULL);
	}
	return 0;
}
