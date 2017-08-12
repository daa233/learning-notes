/**
 * @file: SwapByReference.cpp
 * @description: 通过引用来交换两个整形变量的值
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

void fakeSwap(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swapByPointer(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swapByReference(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main(int argc, char const *argv[]) {
    int n1 = 3, n2 = 5;
    fakeSwap(n1, n2);
    cout << n1 << " " << n2 << endl;    // 3 5
    n1 = 3;
    n2 = 5;
    swapByPointer(&n1, &n2);
    cout << n1 << " " << n2 << endl;    // 5 3
    n1 = 3;
    n2 = 5;
    swapByReference(n1, n2);
    cout << n1 << " " << n2 << endl;    // 5 3
    return 0;
}
