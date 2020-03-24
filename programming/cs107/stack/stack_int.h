#ifndef __stack_int__
#define __stack_int__

typedef struct {
    int* elems;
    int logicalLength;
    int allocLength;
} stack;

void StackNew(stack* s);
void StackDispose(stack* s);
void StackPush(stack* s, int val);
int StackPop(stack* s);
int StackIsEmpty(stack* s);
void StackPrint(stack *s);

#endif