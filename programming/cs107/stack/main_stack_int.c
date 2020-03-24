#include "stack_int.c"
#include "stack_int.h"
#include <stdio.h>

int main()
{
    stack s;
    StackNew(&s);

    StackPrint(&s);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&s));

    int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < sizeof(arr)/sizeof(int); ++i) {
        StackPush(&s, arr[i]);
    }

    StackPrint(&s);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&s));

    int val = StackPop(&s);
    printf("the pop val = %d\n", val);
    StackPrint(&s);

    val = StackPop(&s);
    val = StackPop(&s);
    val = StackPop(&s);
    val = StackPop(&s);

    StackPrint(&s);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&s));

    val = StackPop(&s);

    StackDispose(&s);

    return 0;
}