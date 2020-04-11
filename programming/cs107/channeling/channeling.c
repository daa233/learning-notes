#include <stdio.h>

void DeclareAndInitArray()
{
    int array[10];
    int i;
    for (i = 0; i < 10; ++i) {
        array[i] = i;
    }
}

void PrintArray()
{
    int array[10];
    int i;
    for (i = 0; i < 10; ++i) {
        printf("array[%d] = %d\n", i, array[i]);
    }
}


/**
 * A simple demo of Channeling.
 * Since the function DeclareAndInitArray() and the function PrintArray() have
 * the same activation record, so they are actually operating on the same
 * segment of memory.
 */
int main(int argc, char *argv[])
{
    DeclareAndInitArray();
    PrintArray();

    // Output
    // array[0] = 0
    // array[1] = 1
    // array[2] = 2
    // array[3] = 3
    // array[4] = 4
    // array[5] = 5
    // array[6] = 6
    // array[7] = 7
    // array[8] = 8
    // array[9] = 9
    
    return 0;
}
