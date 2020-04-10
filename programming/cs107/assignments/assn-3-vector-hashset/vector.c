#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
    assert(initialAllocation >= 0);
    if (initialAllocation == 0) {
        v->initAllocSize = 4;   // default initialAllocation value
    } else {
        v->initAllocSize = initialAllocation;
    }
    v->logicSize = 0;
    v->allocSize = v->initAllocSize;
    v->elemSize = elemSize;
    v->freeFn = freeFn;
    v->data = malloc(v->allocSize * v->elemSize);
    assert(v->data != NULL);
}

void VectorDispose(vector *v)
{
    if (v->freeFn != NULL) {
        for (int i = 0; i < v->logicSize; ++i) {
            v->freeFn((char *)v->data + i * v->elemSize);
        }
    }
    free(v->data);
}

int VectorLength(const vector *v)
{
    return v->logicSize;
}

void *VectorNth(const vector *v, int position)
{
    assert(position >= 0 && position <= v->logicSize - 1);
    return (void *)((char *)v->data + position * v->elemSize);
}

/**
 * Method: VectorGrow
 * ------------------
 * Grow the vector by another initialAllocation elements.
 */
static void VectorGrow(vector *v)
{
    v->allocSize += v->initAllocSize;
    v->data = realloc(v->data, v->allocSize * v->elemSize);
    assert(v->data != NULL);
}

void VectorInsert(vector *v, const void *elemAddr, int position)
{
    assert(position >= 0 && position <= v->logicSize);
    if (v->logicSize == v->allocSize)
        VectorGrow(v);
    void *target = (char *)v->data + position * v->elemSize;
    if (position < v->logicSize) {
        int num = v->logicSize - position;
        memmove((char *)target + v->elemSize, target, num * v->elemSize);
    }
    memcpy(target, elemAddr, v->elemSize);
    v->logicSize += 1;
}

void VectorAppend(vector *v, const void *elemAddr)
{
    VectorInsert(v, elemAddr, v->logicSize);
}

void VectorReplace(vector *v, const void *elemAddr, int position)
{
    assert(position >= 0 && position <= v->logicSize - 1);
    void *target = (char *)v->data + position * v->elemSize;
    if (v->freeFn != NULL)
        v->freeFn(target);
    memcpy(target, elemAddr, v->elemSize);
}

void VectorDelete(vector *v, int position)
{
    assert(position >= 0 && position <= v->logicSize - 1);
    void *target = (char *)v->data + position * v->elemSize;
    if (v->freeFn != NULL)
        v->freeFn(target);
    if (position < v->logicSize - 1) {
        memcpy(target, (void *)((char *)target + v->elemSize),
               (v->logicSize - 1 - position) * v->elemSize);
    }
    v->logicSize -= 1;
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{
    assert(searchFn != NULL);
    assert(startIndex >= 0 && startIndex <= v->logicSize);
    void *base = (char *)v->data + startIndex * v->elemSize;
    size_t nmemb = v->logicSize - startIndex;
    void *match;
    if (isSorted) {
        // use binary search
        match = bsearch(key, base, nmemb, v->elemSize, searchFn);
    } else {
        // use linear search
        match = lfind(key, base, &nmemb, v->elemSize, searchFn);
    }
    if (match != NULL) {
        int position = ((char *)match - (char *)base) / v->elemSize;
        return position;
    } else {
        return kNotFound;
    }
} 

void VectorSort(vector *v, VectorCompareFunction compare)
{
    assert(compare != NULL);
    qsort(v->data, v->logicSize, v->elemSize, compare);
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData)
{
    assert(mapFn != NULL);
    for (int i = 0; i < v->logicSize; ++i) {
        void *elemAddr = (char *)v->data + i * v->elemSize;
        mapFn(elemAddr, auxData);
    }
}

