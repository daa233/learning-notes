#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

void call_gettimeofday(unsigned int times) {
    struct timeval current_time;
    for (int i = 0; i < times; ++i) {
        gettimeofday(&current_time, NULL);
    }
}

void call_read(unsigned int times) {
    const char filename[] = "empty.txt";
    char c;
    int fd = open(filename, O_RDONLY, 0);
    for (int i = 0; i < times; ++i) {
        read(fd, &c, 1);
    }
    close(fd);
}

// Get the time cost (ms) of execute given func for `times`
float get_time_cost(void (*func)(unsigned int), unsigned int times) {
    struct timeval tik;
    struct timeval tok;
    gettimeofday(&tik, NULL);
    (*func)(times);
    gettimeofday(&tok, NULL);
    float time_cost = (tok.tv_sec - tik.tv_sec) * 1000. + (tok.tv_usec - tik.tv_usec) / 1000.;
    return time_cost;
}

int main(int argc, char* argv[]) {
    // Usage:
    // ./measure <func_name> <times>

    void (*func)(unsigned int) = NULL;
    unsigned int exec_times = 0;
    if (argc != 3) {
        printf("Error: Unexpected arguments!\nUsage: ./measure <func_name> <times>\n");
        exit(-1);
    } else {
        if (strcmp(argv[1], "gettimeofday") == 0) {
            func = &call_gettimeofday;
        } else if (strcmp(argv[1], "read") == 0) {
            func = &call_read;
        } else {
            printf("Error: Unexpected function! \nChoices: gettimeofday, read\n");
        }
        exec_times = atoi(argv[2]);
    }

    float total_time = get_time_cost(func, exec_times);
    float avg_time = total_time / exec_times;
    printf("Call %s %d times, total_time: %f ms, average time: %f ms\n", argv[1],
           exec_times, total_time, avg_time);

    return 0;
}
