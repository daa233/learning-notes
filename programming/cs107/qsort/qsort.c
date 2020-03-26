#include "qsort.h"
#include <string.h>

void qsort(void *base, size_t nel, size_t elemSize,
           int (*compar)(const void *, const void *))
{
    _qsort_helper(base, 0, nel - 1, elemSize, compar);
}

static void _qsort_helper(void *base, int start, int end, size_t elemSize,
                          int (*compar)(const void *, const void *))
{
    if (start < end)
    {
        int pivotIndex = _partition(base, start, end, elemSize, compar);
        _qsort_helper(base, start, pivotIndex - 1, elemSize, compar);
        _qsort_helper(base, pivotIndex + 1, end, elemSize, compar);
    }
}

static int _partition(void *base, int start, int end, size_t elemSize,
                      int (*compar)(const void *, const void *))
{
    int pivotIndex = end;
    void *pivot = (char *)base + pivotIndex * elemSize;
    int storeIndex = start;
    for (int i = start; i < end; ++i)
    {
        if (compar((char *)base + i * elemSize, pivot) < 0)
        {
            // swap base[i] and base[storeIndex]
            _swap_elem(base, i, storeIndex, elemSize);
            storeIndex++;
        }
    }
    // swap base[storeIndex] and base[pivotIndex]
    _swap_elem(base, storeIndex, pivotIndex, elemSize);
    pivotIndex = storeIndex;

    return pivotIndex;
}

static void _swap_elem(void *base, int i, int j, size_t elemSize)
{
    if (i != j)
    {
        char buffer[elemSize];
        void *iAddr = (char *)base + i * elemSize;
        void *jAddr = (char *)base + j * elemSize;
        memcpy(buffer, iAddr, elemSize);
        memcpy(iAddr, jAddr, elemSize);
        memcpy(jAddr, buffer, elemSize);
    }
}

// compare functions
int IntCmp(const void *elem1, const void *elem2)
{
    return *(int *)elem1 - *(int *)elem2;
}

int StringCmp(const void *elem1, const void *elem2)
{
    return strcmp(*(char **)elem1, *(char **)elem2);
}