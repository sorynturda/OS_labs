#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv) {
    int fd1, fd2;
    char c;
    ssize_t size = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_name> <file_name>\n", argv[0]);
        return -1;
    }

    fd1 = open(argv[1], O_RDONLY);

    if (fd1 == -1) {
        perror("Could not open the input file");
        close(fd1);
        return 1;
    }

    fd2 = creat(argv[2], S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
    if (fd2 == -1) {
        perror("Could not open the output file");
        close(fd2);
        return 1;
    }
    size = lseek(fd1, 0, SEEK_END);
    lseek(fd1, 0, SEEK_SET);
    for (int i = 0; i < size; i++) {
        lseek(fd1, -i-1, SEEK_END);
        read(fd1, &c, 1);
        write(fd2, &c, 1);
    }
    close(fd1);
    close(fd2);
    return 0;
}