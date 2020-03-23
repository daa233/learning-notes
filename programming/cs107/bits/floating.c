#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// modified from https://jameshfisher.com/2017/02/23/printing-bits/
char* get_bits(unsigned char * bytes, size_t num_bytes) {
    char *bits_str = (char *) malloc(num_bytes*(8+1));
    if (!bits_str) return NULL;
    memset(bits_str, ' ', num_bytes*(8+1)); // here ' ' is used for sep
    for (size_t i = 0; i < num_bytes; i++) {
        // display the little endian bytes as big endian
        char byte = bytes[num_bytes-i-1];
        for (int j = 7, k = 0; j >= 0; j--, k++) {
            char ch = byte & (1 << j) ? '1' : '0';
            bits_str[i*9+k] = ch;
        }
    }
    bits_str[num_bytes*9-1] = '\0';
    return bits_str;
}

#define GET_BITS(T, V) ({T x = V; get_bits((unsigned char*) &x, sizeof(x));})


int main()
{
    int a = 37;
    // NOTE: the float points are represented as
    // |+/-|----exp----|------------frac--------------|
    // +/- 1.frac * 2^exp
    float f = *(float *)&a; // interpret the memory of int as float
    char *bs = GET_BITS(int, a);
    printf("int %d (%s) -> float %e\n", a, bs, f);   // int 37 -> float 5.184804e-44
    free(bs);

    f = 7.34;
    short s = *(short *)&f; // interpret the memory of float as short
    char *bs_f = GET_BITS(float, f);
    char *bs_s = GET_BITS(short, s);
    printf("float %e (%s) -> short %d (%s)\n", f, bs_f, s, bs_s);
    free(bs_f);
    free(bs_s);

    return 0;
}

// Output:
// int 37 (00000000 00000000 00000000 00100101) -> float 5.184804e-44
// float 7.340000e+00 (01000000 11101010 11100001 01001000) -> short -7864 (11100001 01001000)