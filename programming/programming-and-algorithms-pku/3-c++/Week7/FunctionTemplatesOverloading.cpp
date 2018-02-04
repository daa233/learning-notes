/**
 * @file: FunctionTemplatesOverloading.cpp
 * @description: 函数模板的重载
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

template <class T1, class T2>
void print(T1 arg1, T2 arg2) {
    cout << "template 1 is called." << endl;
    cout << arg1 << " " << arg2 << endl;
}

template <class T>
void print(T arg1, T arg2) {
    cout << "template 2 is called." << endl;
    cout << arg1 << " " << arg2 << endl;
}

int main(int argc, char const *argv[]) {
    int a = 1, b = 2;
    double c = 3.14;
    print(a, b);
    // template 2 is called.
    // 1 2
    print(a, c);
    // template 1 is called.
    // 1 3.14
    return 0;
}
