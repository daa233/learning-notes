/**
 * @file: SwapTemplate.cpp
 * @description: 编写一个 mySwap() 函数的模板，用于交换任意类型的两个变量的值
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

template<class T>
void mySwap(T &x, T &y) {
    T tmp = x;
    x = y;
    y = tmp;
}

template<class T1, class T2>
T2 print(T1 arg1, T2 arg2) {
    cout << arg1 << " " << arg2 << endl;
    return arg2;
}

int main() {
    int n = 1, m = 2;
    mySwap(n, m);
    cout << n << " " << m << endl;
    double f = 1.2, g = 2.3;
    mySwap(f, g);
    cout << f << " " << g << endl;

    print(n, g);
}
