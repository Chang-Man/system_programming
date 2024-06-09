#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int a = 1, b = 2;
    printf("[%d] parent: a = %d, b = %d\n", getpid(), a, b);

    pid_t pid = fork();

    if (pid > 0) {  // parent
        printf("[%d] parent: pid = %d\n", getpid(), pid);
        printf("[%d] parent: a = %d, b = %d\n", getpid(), a, b);
        a = a * 100;
        sleep(3);
        printf("[%d] parent: a = %d, b = %d\n", getpid(), a, b);
    } else if (pid == 0) {  // child
        printf("[%d] child: pid = %d\n", getpid(), pid);
        printf("[%d] child: a = %d, b = %d\n", getpid(), a, b);
        b = b * 100;
        sleep(2);
        printf("[%d] child: a = %d, b = %d\n", getpid(), a, b);
    }
    return pid < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

