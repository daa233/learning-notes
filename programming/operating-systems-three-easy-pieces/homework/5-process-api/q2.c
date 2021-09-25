#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *filename = "./q2.output";
    int msg_num = 100;
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
    if (fd < 0) {
        // open failed; exit
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(-1);
    }

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        for (int i = 0; i < msg_num; ++i) {
            char msg[100];
            sprintf(msg, "child process message: %d\n", i);
            write(fd, msg, strlen(msg));
        }
    } else {
        // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
        for (int i = 0; i < msg_num; ++i) {
            char msg[100];
            sprintf(msg, "main process message: %d\n", i);
            write(fd, msg, strlen(msg));
        }
    }
    close(fd);
    return 0;
}