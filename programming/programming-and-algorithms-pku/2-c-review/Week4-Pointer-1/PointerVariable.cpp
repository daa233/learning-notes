/**
 * @file: PointerVariable.cpp
 * @description: 观察指针变量示例fun1()和fun2()，体会其中的不同
 *
 * @author: Du Ang
 * @date: Apr. 21st, 2017
 */

#include <iostream>

using namespace std;

void fun1()
{
    int a = 0, b = 0, temp;
    int *p1 = NULL, *p2 = NULL;
    cin >> a >> b;
    p1 = &a;    // p1指向变量a
    p2 = &b;    // p2指向变量b
    if (*p1 < *p2) {
        temp = *p1; *p1 = *p2; *p2 = temp;  // 这里交换的是内存中变量a、b的值
    }
    cout << "max = " << *p1 << ", min = " << *p2 << endl;
}

void fun2()
{
    int a = 0, b = 0;
    int *p1 = NULL, *p2 = NULL;
    int *temp = NULL;
    cin >> a >> b;
    p1 = &a;    // p1指向变量a
    p2 = &b;    // p2指向变量b
    if (*p1 < *p2) {    // 这里交换的是p1和p2的值，即a、b的地址。交换后，p1指向变量b，p2指向变量a
        temp = p1; p1 = p2; p2 = temp;
    }
    cout << "max = " << *p1 << ", min = " << *p2 << endl;
}

int main(int argc, char const *argv[]) {
    fun1();
    fun2();
    return 0;
}
