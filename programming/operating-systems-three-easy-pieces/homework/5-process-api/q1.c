#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int a = 0;
    int b = 0;
    printf("start (pid:%d, a:%d, b:%d)\n", (int)getpid(), a, b);
    a = 1;
    printf("(pid:%d) set a to %d\n", (int)getpid(), a);
    int rc = fork();
    if (rc < 0) {
        // fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        b = 2;
        printf("hello, I am child (pid:%d, a:%d, b:%d)\n", (int)getpid(), a, b);
    } else {
        // parent gose down this path (main)
        sleep(1);  // just sleep to make sure the child process already modify b's value
        b = 1;
        printf("hello, I am parent of %d (pid:%d, a:%d, b:%d)\n", rc, (int)getpid(), a, b);
    }
    return 0;
}
