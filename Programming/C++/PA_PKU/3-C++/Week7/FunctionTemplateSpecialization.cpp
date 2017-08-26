/**
 * @file: FunctionTemplateSpecialization.cpp
 * @description: 函数模板的特化
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>

using namespace std;

template <class T>
void print(T a) {
    cout << a << endl;
}

template <>
void print<double>(double a) {
    cout << scientific << a << endl;
}

int main(int argc, char const *argv[]) {
    int a = 1;
    double b = 2.0;
    char c = 'C';
    string d = "Dog";
    print(a);   // 1
    print(b);   // 2.000000e+00
    print(c);   // C
    print(d);   // Dog
    return 0;
}
