#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    
    if (pid == 0) {
        printf("[%d] child runs\n", getpid());
        while (1); // infinite loop
    } else if (pid > 0) {
        printf("[%d] parent exits\n", getpid());
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}

