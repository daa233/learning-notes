/**
 * @file: FunctionTemplatesAmbiguity.cpp
 * @description: 赋值兼容原则引起函数模板中类型参数的二义性
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

// template <class T>
// T myFunction(T arg1, T arg2) {
//     cout << arg1 << " " << arg2 << endl;
//     return arg1;
// }

template <class T1, class T2>
T1 myFunction(T1 arg1, T2 arg2) {
    cout << arg1 << " " << arg2 << endl;
    return arg1;
}

int main() {
    myFunction(5, 7);       // OK, replace T1 and T2 with int
    myFunction(5.8, 8.4);   // OK, replace T1 and T2 with double
    myFunction(5, 8.4);     // OK, replace T1 with int, replace T2 with double
}
