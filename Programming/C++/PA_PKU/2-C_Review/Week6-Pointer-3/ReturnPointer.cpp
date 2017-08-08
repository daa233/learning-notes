/**
 * @file: ReturnPointer.cpp
 * @description: 指针做函数返回值
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>

using namespace std;

int valueA = 20;
int valueB = 30;

int *get(int arr[][4], int n, int m)
{
    int *pt;
    pt = *(arr + n - 1) + m - 1;
    return(pt);
}

int *getInt1()
{
    int value1 = 20;
    // warning: address of stack memory associated with local variable 'value1' returned
    return &value1;
}

int *getInt2()
{
    int value2 = 30;
    // warning: address of stack memory associated with local variable 'value2' returned
    return &value2;
}

int *getIntA()
{
    return &valueA;
}

int *getIntB()
{
    return &valueB;
}

int *getStaticIntA()
{
    static int staticValueA = 20;
    return &staticValueA;
}

int *getStaticIntB()
{
    static int staticValueB = 30;
    return &staticValueB;
}

int main(int argc, char const *argv[]) {
    int a[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int *pi;
    pi = get(a, 2, 3);
    cout << *pi << endl;

    int *p, *q;
    p = getInt1();
    q = getInt2();
    cout << *p << endl; // mostly print 30, not absolutely

    p = getIntA();
    q = getIntB();
    cout << *p << endl; // 20. The value of global variable valueA

    p = getStaticIntA();
    q = getStaticIntB();
    cout << *p << endl; // 20. The value of static local variable staticValueA

    return 0;
}
