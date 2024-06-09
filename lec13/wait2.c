#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10  // 자식 프로세스의 수를 정의합니다.

int main(int argc, char *argv[]) {
    pid_t pid[N];

    for (int i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            int K = random() % (1 << 20);
            for (int k = 0; k < K; k++);
            exit(100 + i);
        }
    }

    for (int i = 0; i < N; i++) {
        int status;
        pid_t wpid = wait(&status);
        printf("Child %d terminated ", wpid);
        if (WIFEXITED(status)) 
            printf("with status %d\n", WEXITSTATUS(status));
        else 
            printf("abnormally\n");
    }

    return EXIT_SUCCESS;
}

