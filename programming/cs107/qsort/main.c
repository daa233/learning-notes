#include "qsort_int.c"
#include "qsort.c"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // int arr1[] = {2, 6, 8, 4, 5, 9, 7};
    // int nel = sizeof(arr1) / sizeof(int);
    // qsort_int(arr1, nel);
    // for (int i = 0; i < nel; ++i)
    // {
    //     printf("%d ", arr1[i]);
    // }
    // printf("\n");

    int arr2[] = {2, 6, 8, 4, 5, 9, 7};
    int nel = sizeof(arr2) / sizeof(int);
    qsort(arr2, nel, sizeof(int), IntCmp);
    for (int i = 0; i < nel; ++i)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    char *str[] = {"Alice", "Dog", "Elon", "Bob", "Mary"};
    nel = sizeof(str) / sizeof(char *);
    qsort(str, nel, sizeof(char *), StringCmp);
    for (int i = 0; i < nel; ++i)
    {
        printf("'%s' ", str[i]);
    }
    printf("\n");

    return 0;
}
