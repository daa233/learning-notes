#include <stdio.h>

/**
 * Infinite loop demo.
 * To prevent infinite loop, I use another variable to break the loop.
 */
int main(int argc, char *argv[])
{
    int i;
    int j;
    int arr[4];
    printf("the address of i is %p\n", &i);
    printf("the address of j is %p\n", &j);
    printf("the address of arr is %p\n", &arr);
    printf("the difference is %ld\n", (char *)&arr - (char *)&i);

    // we deliberately overite the 4 bytes before the arrays
    for (i = 0, j = 3; j >= -1; --j) {
        arr[j] = 0;
        printf("i = %d, j = %d\n", i, j);
        i += 1;
        if (i > 10) {
            break;
        }
    }

    // Output
    // the address of i is 0x7ffe23183a48
    // the address of j is 0x7ffe23183a4c
    // the address of arr is 0x7ffe23183a50
    // the difference is 8
    // i = 0, j = 3
    // i = 1, j = 2
    // i = 2, j = 1
    // i = 3, j = 0
    // i = 4, j = 0
    // i = 5, j = 0
    // i = 6, j = 0
    // i = 7, j = 0
    // i = 8, j = 0
    // i = 9, j = 0
    // i = 10, j = 0

    return 0;
}