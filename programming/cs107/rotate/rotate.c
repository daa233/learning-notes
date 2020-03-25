#include <stdio.h>
#include <string.h>

void rotate(void *front, void *middle, void *end)
{
    int frontSize = (char *)middle - (char *)front;
    int backSize = (char *)end - (char *)middle;
    char buffer[frontSize];
    memcpy(buffer, front, frontSize);
    memmove(front, middle, backSize);
    memcpy((char *)front + backSize, buffer, frontSize);
}

void rotate_int_array()
{
    int arr[] = {1, 2, 3, 4, 5};
    int middle = 2;
    int elemNum = sizeof(arr) / sizeof(int);
    rotate(arr, arr + middle, arr + elemNum);
    for (int i = 0; i < elemNum; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void rotate_string_array()
{
    char *arr[] = {"Alice", "Bob", "Car", "Dick", "Egg", "Frog"};
    int middle = 3;
    int elemNum = sizeof(arr) / sizeof(char *);
    rotate(arr, arr + middle, arr + elemNum);
    for (int i = 0; i < elemNum; ++i)
    {
        printf("'%s' ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    rotate_int_array();
    rotate_string_array();
    return 0;
}
