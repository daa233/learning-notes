// understand the memory of array
#include <stdio.h>

int main()
{
    int arr[5];
    arr[3] = 128;
    ((short *)arr)[7] = 1;
    printf("%d\n", arr[3]);     // 65664
    return 0;
}
