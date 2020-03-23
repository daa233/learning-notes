#include <stdio.h>
#include <stdlib.h> // for free
#include <string.h> // for memcpy

typedef struct {
    int num;
    int denom;
} fraction;

// generic swap with memory copy
void swap(void* vp1, void* vp2, size_t size)
{
    char buffer[size];
    memcpy(buffer, vp1, size);
    memcpy(vp1, vp2, size);
    memcpy(vp2, buffer, size);
}

int main()
{
    int x = 1, y = 2;
    swap(&x, &y, sizeof(int));
    printf("(int) x = %d, y = %d\n", x, y);

    float a = 1.0, b = 2.0;
    swap(&a, &b, sizeof(float));
    printf("(float) a = %f, b = %f\n", a, b);

    fraction frac1 = { 1, 2 };
    fraction frac2 = { 3, 4 };
    swap(&frac1, &frac2, sizeof(fraction));
    printf("(struct) frac1 = %d/%d, frac2 = %d/%d\n",
        frac1.num, frac1.denom, frac2.num, frac2.denom);

    char* h1 = strdup("hello world");
    char* w1 = strdup("peace and love");
    swap(&h1, &w1, sizeof(char*));
    printf("%s, %s\n", h1, w1);
    free(h1);
    free(w1);

    char* h2 = strdup("hello world");
    char* w2 = strdup("peace and love");
    swap(h2, w2, sizeof(char*)); // forget & here
    printf("%s, %s\n", h2, w2);
    free(h2);
    free(w2);

    return 0;
}

// Output
// (int) x = 2, y = 1
// (float) a = 2.000000, b = 1.000000
// (struct) frac1 = 3/4, frac2 = 1/2
// peace and love, hello world
// peace anrld, hello wod love