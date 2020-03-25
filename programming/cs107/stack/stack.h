#ifndef __stack_int__
#define __stack_int__

typedef struct
{
    void *elems;
    int elemSize;
    int logicalLength;
    int allocLength;
    void (*freeFn)(void *);
    void (*printFn)(void *);
} stack;

void StackNew(stack *s, int elemSize, void (*freeFn)(void *), void (*printFn)(void *));
void StackDispose(stack *s);
void StackPush(stack *s, void *elemAddr);
static void StackGrow(stack *s);
void StackPop(stack *s, void *elemAddr);
int StackIsEmpty(stack *s);
void StackPrint(stack *s);

// type-specific free functions
void IntFree(void *elem);
void StringFree(void *elem);

// type-specific print functions
void IntPrint(void *elem);
void StringPrint(void *elem);

#endif