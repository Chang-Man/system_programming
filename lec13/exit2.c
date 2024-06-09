#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid > 0) {
        sleep(5);
        printf("Parent terminates.\n");
    } else if (pid == 0) {
        while (1) {
            sleep(1);
            printf("Parent's PID is %d.\n", getppid());
        }
    }

    return EXIT_SUCCESS;
}

