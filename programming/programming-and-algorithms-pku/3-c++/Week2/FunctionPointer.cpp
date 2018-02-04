/**
 * @file: FunctionPointer.cpp
 * @description: 函数指针
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 11th, 2017
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

void PrintMin(int a, int b) {
    if (a < b)
        cout << a << endl;
    else
        cout << b << endl;
}

int myCompare(const void * elem1, const void * elem2)
{
    unsigned int *p1, *p2;
    p1 = (unsigned int *) elem1;    // “* elem1” 非法，不知道大小
    p2 = (unsigned int *) elem2;
    return (*p1 % 10) - (*p2 % 10); // 个位数小的排在前面
}

#define NUM 5

int main(int argc, char const *argv[]) {
    void (*pf)(int, int);
    int x = 4, y = 5;
    pf = PrintMin;
    pf(x, y);

    unsigned int an[NUM] = {8, 123, 11, 10, 4};
    qsort(an, NUM, sizeof(unsigned int), myCompare);
    for (int i = 0; i < NUM; i++) {
        cout << an[i] << " ";
    }
    cout << endl;
    return 0;
}
