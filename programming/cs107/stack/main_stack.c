#include "stack.c"
#include "stack.h"
#include <stdio.h>

void test_int_stack()
{
    stack intStack;
    StackNew(&intStack, sizeof(int), IntFree, IntPrint);

    StackPrint(&intStack);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&intStack));

    int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    {
        int copy = arr[i];
        StackPush(&intStack, &copy);
    }

    StackPrint(&intStack);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&intStack));

    int val;
    StackPop(&intStack, &val);

    printf("the pop val = %d\n", val);
    StackPrint(&intStack);

    for (int i = 0; i < 4; ++i)
        StackPop(&intStack, &val);

    StackPrint(&intStack);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&intStack));

    StackDispose(&intStack);
}

void test_string_stack()
{
    const char *friends[] = {"Al", "Bob", "Carol"};
    stack stringStack;
    StackNew(&stringStack, sizeof(char *), StringFree, StringPrint);

    StackPrint(&stringStack);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&stringStack));

    for (int i = 0; i < 3; ++i)
    {
        char *copy = strdup(friends[i]);
        StackPush(&stringStack, &copy);
    }

    StackPrint(&stringStack);
    printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&stringStack));

    char *name;
    for (int i = 0; i < 3; ++i)
    {
        StackPop(&stringStack, &name);
        printf("the pop val = '%s'\n", name);
        free(name);
        StackPrint(&stringStack);
        printf("the stack is empty? (1 for yes, 0 for no) %d\n", StackIsEmpty(&stringStack));
    }

    StackDispose(&stringStack);
}

int main(int argc, char const *argv[])
{
    test_int_stack();
    test_string_stack();
    return 0;
}
