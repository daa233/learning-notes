/**
 * @file: Decltype.cpp
 * @description: C++11 新特性，decltype 关键字
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>
#include <typeinfo> // typeid()

using namespace std;

int main(int argc, char const *argv[]) {
    int i;
    double t;
    struct A {
        double x;
    };
    const A *a = new A();

    decltype(a) x1;             // x1 is A *
    decltype(i) x2;             // x2 is int
    decltype(a->x) x3;          // x3 is double
    decltype((a->x)) x4 = t;    // x4 is double &
    // run with command '| c++filt'
    cout << typeid(x1).name() << endl;  // main::A const*
    cout << typeid(x2).name() << endl;  // int
    cout << typeid(x3).name() << endl;  // double
    cout << typeid(x4).name() << endl;  // double
    return 0;
}
