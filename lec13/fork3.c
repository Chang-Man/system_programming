#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void read_bytes(int fd, int n) {
    char c;
    while ((n == -1) || (n-- > 0)) {
        if (read(fd, &c, 1) < 1) break;
        printf("[%d] %c\n", getpid(), c);
        sleep(2);
    }
}

int main(int argc, char *argv[]) {
    int fd = argc == 1 ? STDIN_FILENO : open(argv[1], O_RDONLY);
    if (fd < 0) return EXIT_FAILURE;

    read_bytes(fd, 3);

    pid_t pid = fork();

    if (pid > 0) {  // parent
        sleep(1);
        read_bytes(fd, -1);
    } else if (pid == 0) {  // child
        read_bytes(fd, -1);
    }

    return pid < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

