// use prameter as the arrray size
#include <stdio.h>

void f(int n)
{
    // wrong, variable-sized object may not be initialized
    // refers to https://stackoverflow.com/questions/3082914/c-compile-error-variable-sized-object-may-not-be-initialized
    // char str[n] = "hello";

    // right
    char str[n];
    str[0] = 'h';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';
    printf("%s\n", str);
}

int main()
{
    f(10);
    return 0;
}