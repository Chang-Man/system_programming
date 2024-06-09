#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == -1) return EXIT_FAILURE;

    if (pid == 0) {
        printf("[%d] hello from child.\n", getpid());
    } else {
        int status;
        printf("[%d] hello from parent.\n", getpid());
        wait(&status);
        printf("[%d] child %d has terminated with status %d.\n", getpid(), pid, WEXITSTATUS(status));
    }

    printf("Bye\n");
    return EXIT_SUCCESS;
}

