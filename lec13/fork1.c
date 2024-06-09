#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Cannot fork child");
        return EXIT_FAILURE;
    }

    printf("pid = %d, my pid = %d, parent's pid = %d\n", pid, getpid(), getppid());

    return EXIT_SUCCESS;
}

