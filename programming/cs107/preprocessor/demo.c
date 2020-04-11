#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include <string.h>

/**
 * Demo 1
 * Test commenting #include <stdlib.h>
 */
void demo1()
{
    void *a = malloc(10 * sizeof(int));
    assert(a != NULL);
    printf("Yah!\n");
    free(a);
}


/**
 * Demo 2
 * Test commenting #include <string.h> and using a different declariation
 *  of strlen
 */
int strlen(char *str, int n);

void demo2()
{
    int a = 65;
    int length = strlen((char *)&a, a);
    // 'length a = 1' for little median machines, the first byte of integer 65
    printf("length a = %d\n", length);
    int b = 0;
    length = strlen((char *)&b, b);
    printf("length b = %d\n", length);  // length b = 0
    int c = 65535;
    length = strlen((char *)&c, c);
    printf("length c = %d\n", length);  // length c = 2
}


int main(int argc, char *argv[])
{
    // demo1();
    demo2();
    return 0;
}
