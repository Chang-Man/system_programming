#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

void int_hdl(int sig) {
    printf("Received SIGINT\n");
}

void alarm_hdl(int sig) {
    sigset_t set;
    char sigset[32];

    if (sigpending(&set) >= 0) {
        for (int i = 0; i < 32; i++)
            sigset[i] = (sigismember(&set, i)) > 0 ? 'P' : '.';
        sigset[0] = ' ';
        sigset[31] = '\0';
        printf("Pending signals: %s\n", sigset);
    }

    alarm(1);
}

int main(int argc, char *argv[]) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    if (signal(SIGALRM, alarm_hdl) == SIG_ERR) {
        perror("Cannot install signal handler");
        return EXIT_FAILURE;
    }

    if (signal(SIGINT, int_hdl) == SIG_ERR) {
        perror("Cannot install signal handler");
        return EXIT_FAILURE;
    }

    alarm(1);

    struct timespec delay = { .tv_sec = 5, .tv_nsec = 0 };
    while ((nanosleep(&delay, &delay) < 0) && (errno == EINTR));

    if (sigprocmask(SIG_BLOCK, &set, NULL) == 0)
        printf("SIGINT is now blocked.\n");

    delay.tv_sec = 5; delay.tv_nsec = 0;
    while ((nanosleep(&delay, &delay) < 0) && (errno == EINTR));

    if (sigprocmask(SIG_UNBLOCK, &set, NULL) == 0)
        printf("SIGINT is now unblocked.\n");

    delay.tv_sec = 5; delay.tv_nsec = 0;
    while ((nanosleep(&delay, &delay) < 0) && (errno == EINTR));

    return EXIT_SUCCESS;
}

