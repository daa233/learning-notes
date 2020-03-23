#include <stdio.h>
#include <stdlib.h> // for free
#include <string.h> // for memcpy

// generic linear search
void* lsearch(void* key,
    void* base,
    size_t n,
    size_t elemSize,
    int (*cmpFn)(void*, void*))
{
    for (int i = 0; i < n; ++i) {
        // use (char *) trick to get the offset of elemAddr
        void* elemAddr = (char*)base + i * elemSize;
        if (cmpFn(key, elemAddr) == 0)
            return elemAddr;
    }
    return NULL;
}

// int type compare function
int IntCmp(void* elem1, void* elem2)
{
    int* ip1 = elem1;
    int* ip2 = elem2;
    return *ip1 - *ip2;
}
// char * stype compare function
int StrCmp(void* elem1, void* elem2)
{
    char* vp1 = *(char**)elem1;
    char* vp2 = *(char**)elem2;
    return strcmp(vp1, vp2);
}

int main()
{
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int key = 5;
    int* found = lsearch(&key, arr, 10, sizeof(int), &IntCmp);
    if (found) {
        printf("%d\n", *found);
    } else {
        printf("not found\n");
    }

    char* notes[] = { "Ab", "F#", "B", "Gb", "D" };
    char* favoriteNote = "Eb";
    char** foundNote = lsearch(&favoriteNote, notes, 5, sizeof(char*), &StrCmp);
    if (foundNote) {
        printf("%s\n", *foundNote);
    } else {
        printf("not found\n");
    }

    // use the bsearch in the standard library
    found = bsearch(&key, arr, 10, sizeof(int), &IntCmp); // with a warning about const
    if (found) {
        printf("%d\n", *found);
    } else {
        printf("not found\n");
    }
    return 0;
}

// Output
// 5
// not found
// 5