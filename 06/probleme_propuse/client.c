#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    pid_t pid;
    printf("> ");
    int x, y, status;
    char c;
    scanf("%d %d %c", &x, &y, &c);
    pid = fork();
    if(!pid){
        char buff1[5], buff2[5], buff3[5];
        sprintf(buff1, "%d", x);
        sprintf(buff2, "%d", y);
        buff3[0] = c;
        buff3[1] = 0;
        execl("server", "server", buff1, buff2, buff3, NULL);
        perror("error");
    }else{
        wait(&status);
        printf("%d %c %d = %d\n", x,c,y, WEXITSTATUS(status));
    }
    return 0;
}