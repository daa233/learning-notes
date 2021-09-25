#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void fork_failed() {
    fprintf(stderr, "fork failed\n");
    exit(1);
}

void pipe_failed() {
    perror("pipe failed");
    exit(2);
}

int main(int argc, char* argv[]) {
    // main_process --fork-- child_process_1
    //      |                 /
    //     fork              /
    //        \            |/
    //        child_process_2

    int buffer_size = 100;
    char buffer[buffer_size];
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        pipe_failed();
    }

    int rc1 = fork();
    if (rc1 < 0) {
        // fork failed; exit
        fork_failed();
    } else if (rc1 == 0) {
        // child process 1
        close(pipefd[0]);  // close unused read end
        char msg[buffer_size];
        sprintf(msg, "message from child process 1 (pid:%d)\n", (int)getpid());
        // write message to the pipe
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);  // close write end
        printf("child process 1 (pid:%d) ends\n", (int)getpid());
    } else {
        int rc2 = fork();
        if (rc2 < 0) {
            // fork failed; exit
            fork_failed();
        } else if (rc2 == 0) {
            // child process 2
            close(pipefd[1]);  // close unused write end
            // read message from the pipe
            while (read(pipefd[0], &buffer, buffer_size) > 0) {
                printf("In child process 2 (pid:%d): %s", (int)getpid(), buffer);
            }
            close(pipefd[0]);  // close read end
            printf("child process 2 (pid:%d) ends\n", (int)getpid());
        } else {
            // parent goes down this path (main)
            close(pipefd[0]);  // close unused read end
            close(pipefd[1]);  // close unused write end
            printf("hello, I am parent of %d,%d (pid:%d)\n", rc1, rc2, (int)getpid());
        }
    }
    return 0;
}
