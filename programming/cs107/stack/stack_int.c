#include "stack_int.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void StackNew(stack* s)
{
    int initAllocSize = 4;
    s->elems = (int*)malloc(initAllocSize * sizeof(int));
    assert(s->elems != NULL);
    s->logicalLength = 0;
    s->allocLength = initAllocSize;
}

void StackDispose(stack* s)
{
    free(s->elems);
    s->logicalLength = 0;
    s->allocLength = 0;
}

void StackPush(stack* s, int val)
{
    if (s->logicalLength == s->allocLength) {
        s->allocLength *= 2;
        s->elems = realloc(s->elems, s->allocLength * sizeof(int));
        assert(s->elems != NULL);
    }
    s->elems[s->logicalLength] = val;
    s->logicalLength += 1;
}

int StackPop(stack* s)
{
    // this version may cause memory leackage
    // assert(s->logicalLength > 0);
    // s->logicalLength -= 1;
    // return s->elems[s->logicalLength];

    if (s->logicalLength > 0) {
        s->logicalLength -= 1;
        return s->elems[s->logicalLength];
    } else {
        printf("ERROR: Can't pop when the stack is empty!\n");
        return 0;
    }
}

int StackIsEmpty(stack* s) { return s->logicalLength == 0; }

void StackPrint(stack* s)
{
    printf("[ ");
    for (int i = 0; i < s->logicalLength; ++i) {
        printf("%d ", s->elems[i]);
    }
    printf("]\n");
}