/**
 * @file: ArrayAndPointer.cpp
 * @description:
 *
 * @author: Du Ang
 * @date: Apr. 22nd, 2017
 */

#include <iostream>

using namespace std;

// 利用指针遍历多维数组元素
void fun1()
{
    int a[3][4] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
    int *p;
    for (p = &a[0][0]; p < &a[0][0] + 12; p++) {
        cout << p << " " << *p << endl;
    }
}

// 利用指针变量引用多维数组
void fun2()
{
    int a[3][4] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
    // a相当于指向a[3][4]的“第一个元素”的指针，而“第一个元素”是指一个“包含4个int型元素的一位数组”
    // 所以 a 相当于一个“包含4个int型元素的一位数组”的地址
    // 即 p 的基类型应该是“包含4个int型元素的一位数组”
    int (*p)[4], i, j;
    p = a;
    cin >> i >> j;
    cout << setw(4) << *(*(p+i)+j) << endl;
}

int main(int argc, char const *argv[]) {
    fun1();
    return 0;
}
