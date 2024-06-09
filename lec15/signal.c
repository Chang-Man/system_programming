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

void alarm_hdl(int sig) {
    printf("Wake up!\n");
    alarm(5);
}

int main(int argc, char *argv[]) {
    struct sigaction action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);  // allow nested signals
    action.sa_flags = SA_RESTART | SA_NODEFER;  // restart syscalls if possible

    if (sigaction(SIGINT, &action, NULL) < 0) {
        perror("Cannot install signal handler");
        return EXIT_FAILURE;
    }

    if (signal(SIGALRM, alarm_hdl) == SIG_ERR) {
        perror("Cannot install signal handler");
        return EXIT_FAILURE;
    }

    alarm(5);
    while (pause() == -1);

    return EXIT_SUCCESS;
}

