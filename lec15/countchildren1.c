#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define N 16
volatile int counter = 0;

void handler(int sig) {
    int child_status;
    pid_t wpid = wait(&child_status);
    if (WIFEXITED(child_status))
        printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
    else
        printf("Child %d terminated abnormally\n", wpid);

    counter++;
}

int main(int argc, char *argv[]) {
    pid_t pid[N];
    if (signal(SIGCHLD, handler) == SIG_ERR) return EXIT_FAILURE;

    printf("Creating %d children...\n", N);
    for (int i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            sleep(i/2);
            return 100+i;
        }
    }

    for (int i = 0; i < N; i += 2) {
        printf("Killing process %d\n", pid[i]);
        kill(pid[i], SIGINT);
    }

    printf("Waiting until all %d children have terminated...\n", N);
    while (counter < N) {
        sleep(1);
        printf("--> %d / %d terminated.\n", counter, N);
    }

    return EXIT_SUCCESS;
}

