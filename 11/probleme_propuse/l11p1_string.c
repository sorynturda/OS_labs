#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    int fd[2];
    char s[26] = "X";

    if (pipe(fd) != 0) {
        perror("Could not create pipe");
        return 1;
    }

    if (fork() != 0) {
        //parent
        close(fd[0]); //no use for read end
        strcpy(s, "String pentru pipe\0");
        for (int i = 0; i <= strlen(s); i++)
            write(fd[1], &s[i], 1);
        printf("Parent: wrote '%s' to pipe\n", s);
        close(fd[1]);
        wait(NULL);
    } else {
        //child
        close(fd[1]); //no use for write end
        printf("Child: read '");
        char c;
        for (;;) {
            read(fd[0], &c, 1);
            printf("%c", c);
            if (c == 0)
                break;
        }
        printf("' from pipe\n");
        close(fd[0]);
    }

    return 0;
}
