#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    static int level = 0;
    
    level++;
    printf("[nesting level %d] Hohoo, got signal %d\n", level, sig);
    sleep(3);
    level--;
}

int main() {
    struct sigaction action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);  // 다른 시그널을 블록하지 않습니다.
    action.sa_flags = SA_NODEFER;  // 동일한 시그널의 중첩을 허용합니다.

    if (sigaction(SIGINT, &action, NULL) < 0) {
        perror("Cannot install signal handler");
        return EXIT_FAILURE;
    }

    while (1) {
        pause();  // 시그널을 받을 때까지 대기합니다.
    }

    return EXIT_SUCCESS;
}

