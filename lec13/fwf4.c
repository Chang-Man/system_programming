#include <stdio.h>
#include <unistd.h>

void fwf4() {
    printf("L0\n");
    printf("init - [%d]\n", getpid());
    if (fork() == 0) {
        printf("L1\n");
        if (fork() == 0) {
            printf("L2\n");
            fork();
        }
	printf("L1 ppid - [%d]\n", getppid());
    }
    printf("Bye\n");
}

int main() {
    fwf4();
    return 0;
}

