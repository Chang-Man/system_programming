#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid = fork();

    char *exec_argv[] = {
        "/bin/ls",
        "-l",
        "/usr/bin",
        NULL,
    };

    if (pid == -1) return EXIT_FAILURE;

    if (pid == 0) {
        if (execve(exec_argv[0], exec_argv, envp) < 0) {
            perror("Cannot execute program");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        if (wait(&status) > 0) {
            printf("Process exited with status %d.\n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}

