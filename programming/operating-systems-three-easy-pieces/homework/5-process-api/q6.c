#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        int stat_loc = 0;
        int wc = wait(&stat_loc);
        printf("hello, I am child (pid:%d, wc:%d, stat_loc:%d)\n", (int)getpid(), wc, stat_loc);
    } else {
        // parent goes down this path (main)
        int wc = waitpid(rc, NULL, WUNTRACED);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
    return 0;
}
