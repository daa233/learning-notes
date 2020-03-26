#include <stdio.h>

void qsort_int(int *base, size_t nel);
static void _qsort_int_helper(int *base, int start, int end);
static int _partition_int(int *base, int start, int end);
static void _swap_int_elem(int *base, int i, int j);
