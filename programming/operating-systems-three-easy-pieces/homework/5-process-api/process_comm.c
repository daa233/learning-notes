#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

char *DEFAULT_CONTENT = "hello";

typedef struct Task {
    char executor[100];
    char content[1000];
} Task;

void fork_failed() {
    fprintf(stderr, "fork failed\n");
    exit(1);
}

void pipe_failed() {
    perror("pipe failed");
    exit(2);
}

int main(int argc, char *argv[]) {
    // main_process <== pipe ==> child_process_1
    //        |\\                 //|
    //          \\               //
    //          pipe           pipe
    //            \\           //
    //             \\|       |//
    //            child_process_2

    int buffer_size = 100;
    int pipefd_main_child1[2];
    int pipefd_child1_main[2];
    int pipefd_main_child2[2];
    int pipefd_child2_main[2];
    int pipefd_child1_child2[2];
    int pipefd_child2_child1[2];
    char main_child1_buffer[buffer_size];
    char child1_main_buffer[buffer_size];
    char main_child2_buffer[buffer_size];
    char child2_main_buffer[buffer_size];
    char child1_child2_buffer[buffer_size];
    char child2_child1_buffer[buffer_size];
    int freq = 3;
    int DEBUG = 1;

    srand(time(NULL));  // Initialization, should only be called once.

    if (pipe(pipefd_main_child1) == -1) {
        pipe_failed();
    }
    if (pipe(pipefd_child1_main) == -1) {
        pipe_failed();
    }
    if (pipe(pipefd_main_child2) == -1) {
        pipe_failed();
    }
    if (pipe(pipefd_child2_main) == -1) {
        pipe_failed();
    }
    if (pipe(pipefd_child1_child2) == -1) {
        pipe_failed();
    }
    if (pipe(pipefd_child2_child1) == -1) {
        pipe_failed();
    }

    int rc1 = fork();
    if (rc1 < 0) {
        // fork failed; exit
        fork_failed();
    } else if (rc1 == 0) {
        // child process 1
        printf("In child process 1 (pid:%d)\n", (int)getpid());
        time_t now;

        close(pipefd_main_child1[1]);
        close(pipefd_main_child2[0]);
        close(pipefd_main_child2[1]);
        close(pipefd_child1_main[0]);
        close(pipefd_child2_main[0]);
        close(pipefd_child2_main[1]);
        close(pipefd_child1_child2[0]);
        close(pipefd_child2_child1[1]);

        while (1) {
            if (DEBUG)
                printf("child1 loop, start\n");

            fcntl(pipefd_main_child1[0], F_SETFL, O_NONBLOCK);
            fcntl(pipefd_child2_child1[0], F_SETFL, O_NONBLOCK);
            fcntl(pipefd_child1_main[1], F_SETFL, O_NONBLOCK);
            fcntl(pipefd_child1_child2[1], F_SETFL, O_NONBLOCK);

            while (read(pipefd_main_child1[0], &main_child1_buffer, buffer_size) > 0) {
                printf("[child1 (pid:%d)] - receive message: %s\n", (int)getpid(), main_child1_buffer);
            }
            while (read(pipefd_child2_child1[0], &child2_child1_buffer, buffer_size) > 0) {
                printf("[child1 (pid:%d)] - receive message: %s\n", (int)getpid(), child2_child1_buffer);
            }

            if (DEBUG)
                printf("child1 loop, after read\n");

            // randomly send message to child processes
            int t = rand() % freq;  // rand() returns a pseudo-random integer between 0 and RAND_MAX
            char msg[buffer_size];

            if (t == 0) {
                // send message to main process
                time(&now);
                sprintf(msg, "child1 process (pid:%d): [%s]\n", (int)getpid(), ctime(&now));
                // write message to the pipe
                write(pipefd_child1_main[1], msg, strlen(msg) + 1);
            } else if (t == 1) {
                // send message to child process 2
                time(&now);
                sprintf(msg, "child1 process (pid:%d): [%s]\n", (int)getpid(), ctime(&now));
                // write message to the pipe
                write(pipefd_child1_child2[1], msg, strlen(msg) + 1);
            } else {
                sleep(t);
            }

            if (DEBUG)
                printf("child1 loop, finish\n");
        }
    } else {
        int rc2 = fork();
        if (rc2 < 0) {
            // fork failed; exit
            fork_failed();
        } else if (rc2 == 0) {
            // child process 2
            printf("In child process 2 (pid:%d)\n", (int)getpid());
            time_t now;

            close(pipefd_main_child1[0]);
            close(pipefd_main_child1[1]);
            close(pipefd_main_child2[1]);
            close(pipefd_child1_main[0]);
            close(pipefd_child1_main[1]);
            close(pipefd_child2_main[0]);
            close(pipefd_child1_child2[0]);
            close(pipefd_child1_child2[1]);
            close(pipefd_child2_child1[0]);
            close(pipefd_child2_child1[1]);

            while (1) {
                if (DEBUG)
                    printf("child2 loop, start\n");

                fcntl(pipefd_main_child2[0], F_SETFL, O_NONBLOCK);
                fcntl(pipefd_child1_child2[0], F_SETFL, O_NONBLOCK);
                fcntl(pipefd_child2_main[1], F_SETFL, O_NONBLOCK);
                fcntl(pipefd_child2_child1[1], F_SETFL, O_NONBLOCK);

                while (read(pipefd_main_child2[0], &main_child2_buffer, buffer_size) > 0) {
                    printf("[child2 (pid:%d)] - receive message: %s\n", (int)getpid(), main_child2_buffer);
                }
                while (read(pipefd_child1_child2[0], &child1_child2_buffer, buffer_size) > 0) {
                    printf("[child2 (pid:%d)] - receive message: %s\n", (int)getpid(), child1_child2_buffer);
                }

                if (DEBUG)
                    printf("child2 loop, after read\n");

                // randomly send message to child processes
                int t = rand() % freq;  // rand() returns a pseudo-random integer between 0 and RAND_MAX
                char msg[buffer_size];

                if (t == 0) {
                    // send message to main process
                    time(&now);
                    sprintf(msg, "child2 process (pid:%d): %s\n", (int)getpid(), ctime(&now));
                    // write message to the pipe
                    write(pipefd_child2_main[1], msg, strlen(msg) + 1);
                } else if (t == 1) {
                    // send message to child process 1
                    time(&now);
                    sprintf(msg, "child2 process (pid:%d): %s\n", (int)getpid(), ctime(&now));
                    // write message to the pipe
                    write(pipefd_child2_child1[1], msg, strlen(msg) + 1);
                } else {
                    sleep(t);
                }

                if (DEBUG)
                    printf("child2 loop, finish\n");
            }
        } else {
            // parent goes down this path (main)
            printf("hello, I am parent of %d & %d (pid:%d)\n", rc1, rc2, (int)getpid());
            time_t now;

            close(pipefd_main_child1[0]);
            close(pipefd_main_child2[0]);
            close(pipefd_child1_main[1]);
            close(pipefd_child2_main[1]);
            close(pipefd_child1_child2[0]);
            close(pipefd_child1_child2[1]);
            close(pipefd_child2_child1[0]);
            close(pipefd_child2_child1[1]);

            while (1) {
                if (DEBUG)
                    printf("main loop start\n");

                fcntl(pipefd_child1_main[0], F_SETFL, O_NONBLOCK);
                fcntl(pipefd_child2_main[0], F_SETFL, O_NONBLOCK);
                fcntl(pipefd_main_child1[1], F_SETFL, O_NONBLOCK);
                fcntl(pipefd_main_child2[1], F_SETFL, O_NONBLOCK);

                while (read(pipefd_child1_main[0], &child1_main_buffer, buffer_size) > 0) {
                    printf("[main (pid:%d)] - receive message: %s", (int)getpid(), child1_main_buffer);
                }
                while (read(pipefd_child2_main[0], &child2_main_buffer, buffer_size) > 0) {
                    printf("[main (pid:%d)] - receive message: %s", (int)getpid(), child2_main_buffer);
                }

                if (DEBUG)
                    printf("main loop, after read\n");

                // randomly send message to child processes
                int t = rand() % freq;  // rand() returns a pseudo-random integer between 0 and RAND_MAX

                if (t == 0) {
                    // send message to child process 1
                    time(&now);
                    char msg[buffer_size];
                    sprintf(msg, "main process (pid:%d): %s\n", (int)getpid(), ctime(&now));
                    // write message to the pipe
                    write(pipefd_main_child1[1], msg, strlen(msg) + 1);
                } else if (t == 1) {
                    // send message to child process 2
                    time(&now);
                    char msg[buffer_size];
                    sprintf(msg, "main process (pid:%d): %s\n", (int)getpid(), ctime(&now));
                    // write message to the pipe
                    write(pipefd_main_child2[1], msg, strlen(msg) + 1);
                } else {
                    sleep(t);
                }

                if (DEBUG)
                    printf("main loop, finish\n");
            }
        }
    }
    return 0;
}
