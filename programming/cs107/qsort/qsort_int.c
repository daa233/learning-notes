#include "qsort_int.h"

void qsort_int(int *base, size_t nel)
{
    _qsort_int_helper(base, 0, nel - 1);
}

static void _qsort_int_helper(int *base, int start, int end)
{
    if (start < end)
    {
        int pivotIndex = _partition_int(base, start, end);
        _qsort_int_helper(base, start, pivotIndex - 1);
        _qsort_int_helper(base, pivotIndex + 1, end);
    }
}

static int _partition_int(int *base, int start, int end)
{
    int pivotIndex = end;
    int pivot = base[pivotIndex];
    int storeIndex = start;
    for (int i = start; i < end; ++i)
    {
        if (base[i] < pivot)
        {
            // swap base[i] and base[storeIndex]
            _swap_int_elem(base, i, storeIndex);
            storeIndex++;
        }
    }
    // swap base[storeIndex] and base[pivotIndex]
    _swap_int_elem(base, storeIndex, pivotIndex);
    pivotIndex = storeIndex;

    return pivotIndex;
}

static void _swap_int_elem(int *base, int i, int j)
{
    if (i != j)
    {
        int temp = base[i];
        base[i] = base[j];
        base[j] = temp;
    }
}