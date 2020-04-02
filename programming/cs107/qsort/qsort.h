#ifndef __qsort_h__
#define __qsort_h__

#include <stdio.h>

void qsort(void *base, size_t nel, size_t elemSize,
           int (*compar)(const void *, const void *));

static void _qsort_helper(void *base, int start, int end, size_t elemSize,
                          int (*compar)(const void *, const void *));

static int _partition(void *base, int start, int end, size_t elemSize,
                      int (*compar)(const void *, const void *));

static void _swap_elem(void *base, int i, int j, size_t elemSize);

// compare functions
int IntCmp(const void *elem1, const void *elem2);

int StringCmp(const void *elem1, const void *elem2);

#endif