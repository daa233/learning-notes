/*
 * References:
 *   - https://stackoverflow.com/questions/15017102/commands-like-ls-l-not-executing-in-execl-whereas-in-execvp-it-works
 *   - https://linuxhint.com/exec_linux_system_call_c/
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int call_execl() {
    printf("########## call execl ##########\n");
    return execl("/bin/ls", "ls", "-l", "./", NULL);
}

int call_execle() {
    printf("########## call execle ##########\n");
    return execle("/bin/ls", "ls", "-l", "./", NULL);

    // NOTE: Here is an example to use environment variable, only work with shell command.
    // char *const env[] = {
    //     "DIR=/usr/local",
    //     NULL,
    // };
    // return execle("/bin/bash", "bash", "-c", "ls -l $DIR", NULL, env);
}

int call_execlp() {
    // `execlp`: `execl` with `PATH` env
    printf("########## call execlp ##########\n");
    return execlp("ls", "ls", "-l", "./", NULL);
}

int call_execv() {
    // `execv`: `execl` with packed args
    printf("########## call execv ##########\n");
    char *myargs[4];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = strdup("-l");
    myargs[2] = strdup("./");
    myargs[3] = NULL;
    return execv(myargs[0], myargs);
}

int call_execvp() {
    // `execvp`: `execv` with `PATH` env
    printf("########## call execvp ##########\n");
    char *myargs[4];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("-l");
    myargs[2] = strdup("./");
    myargs[3] = NULL;
    return execvp(myargs[0], myargs);
}

int call_execvP() {
    // `execvP`: `execvp` with a search path arg
    printf("########## call execvP ##########\n");
    char *myargs[4];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("-l");
    myargs[2] = strdup("./");
    myargs[3] = NULL;
    return execvP(myargs[0], "/usr/bin:/bin", myargs);
}

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process goes down this path
        printf("hello, I am child (pid:%d)\n", (int)getpid());

        // now exec "ls" with different functions in exec family
        if (argc == 1 || strcmp(argv[1], "execl") == 0) {
            call_execl();  // run `ls` by `execl`
        } else if (argc == 2 && strcmp(argv[1], "execle") == 0) {
            call_execle();  // run `ls` by `execle`
        } else if (argc == 2 && strcmp(argv[1], "execlp") == 0) {
            call_execlp();  // run `ls` by `execlp`
        } else if (argc == 2 && strcmp(argv[1], "execv") == 0) {
            call_execv();  // run `ls` by `execv`
        } else if (argc == 2 && strcmp(argv[1], "execvp") == 0) {
            call_execvp();  // run `ls` by `execvp`
        } else if (argc == 2 && strcmp(argv[1], "execvP") == 0) {
            call_execvP();  // run `ls` by `execvP`
        } else if (argc == 2) {
            printf("unrecoginized exec method: %s!\n", argv[1]);
        }
        printf("this shouldn't print out\n");
    } else {
        // parent goes down this path (main)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
    return 0;
}
