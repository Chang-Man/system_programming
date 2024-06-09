#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define N 16  // 자식 프로세스의 수를 정의합니다.

int main(int argc, char *argv[]) {
    pid_t pid[N];
    int i, child_status;

    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {  // child: sleep for certain amount of time
            sleep(i / 2);
            return 100 + i;
        } else {  // parent: report
            printf("Created process %d\n", pid[i]);
        }
    }

    for (i = 0; i < N; i += 2) {  // parent: send SIGINT to half of children
        printf("Killing process %d\n", pid[i]);
        kill(pid[i], SIGINT);
    }

    for (i = 0; i < N; i++) {  // parent: wait for children to terminate
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status)) {
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        } else {
            printf("Child %d terminated abnormally\n", wpid);
        }
    }
    return 0;
}

