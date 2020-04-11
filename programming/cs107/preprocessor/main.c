#include <stdio.h>
#include <assert.h>

#define A(expr) ((void)0)

#define MAX(a, b) a > b ? a : b

int main(int argc, char *argv[])
{
    A(1);       // null statement
    (void)0;    // null statement

    int a = 1;
    int b = 2;
    int c = MAX(a, b);
    assert(c >= a);

    printf("%d\n", c);
    return 0;
}