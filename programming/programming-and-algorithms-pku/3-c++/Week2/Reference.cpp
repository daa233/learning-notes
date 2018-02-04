/**
 * @file: Reference.cpp
 * @description: 引用
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

void fun1()
{
    int n = 7;
    int &r = n;
    r = 4;
    cout << r << endl;  // 4
    cout << n << endl;  // 4
    n = 5;
    cout << r << endl;  // 5
}

void fun2()
{
    double a = 4, b = 5;
    double &r1 = a;
    double &r2 = r1;    // r2 也引用 a
    r2 = 10;
    cout << a << endl;  // 10
    r1 = b;             // r1 并没有引用 b
    cout << a << endl;
}

int main(int argc, char const *argv[]) {
    fun1();
    fun2();
    return 0;
}
