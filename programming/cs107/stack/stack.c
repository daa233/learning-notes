#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StackNew(stack *s, int elemSize, void (*freeFn)(void *),
              void (*printFn)(void *))
{
    assert(elemSize > 0);
    s->allocLength = 4;
    s->logicalLength = 0;
    s->elemSize = elemSize;
    s->freeFn = freeFn;
    s->printFn = printFn;
    s->elems = malloc(s->allocLength * s->elemSize);
    assert(s->elems != NULL);
}

void StackDispose(stack *s)
{
    if (s->freeFn != NULL)
    {
        for (int i = 0; i < s->logicalLength; ++i)
        {
            s->freeFn((char *)s->elems + i * s->elemSize);
        }
    }
    free(s->elems);
}

void StackPush(stack *s, void *elemAddr)
{
    if (s->logicalLength == s->allocLength)
        StackGrow(s);
    void *target = (char *)s->elems + s->logicalLength * s->elemSize;
    memcpy(target, elemAddr, s->elemSize);
    s->logicalLength += 1;
}

static void StackGrow(stack *s)
{
    s->allocLength *= 2;
    s->elems = realloc(s->elems, s->allocLength * s->elemSize);
    assert(s->elems != NULL);
}

void StackPop(stack *s, void *elemAddr)
{
    assert(s->logicalLength > 0);
    s->logicalLength -= 1;
    void *source = (char *)s->elems + s->logicalLength * s->elemSize;
    memcpy(elemAddr, source, s->elemSize);
}

int StackIsEmpty(stack *s)
{
    return s->logicalLength == 0;
}

void StackPrint(stack *s)
{
    printf("[ ");
    for (int i = 0; i < s->logicalLength; ++i)
        s->printFn((char *)s->elems + i * s->elemSize);
    printf("]\n");
}

// free function for int
void IntFree(void *elem) {}

// free function for c-string
void StringFree(void *elem)
{
    free(*(char **)elem);
}

// print function for int
void IntPrint(void *elem)
{
    printf("%d ", *(int *)elem);
}

// print function for c-string
void StringPrint(void *elem)
{
    printf("'%s' ", *(char **)elem);
}
