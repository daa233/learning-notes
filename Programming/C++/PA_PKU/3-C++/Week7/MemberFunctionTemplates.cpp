/**
 * @file: MemberFunctionTemplates.cpp
 * @description: 函数模板作为类模板成员
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>

using namespace std;

template <class T>
class A {
public:
    template <class T2>
    void func(T2 t) { cout << t << endl; }  // member function template
};

int main(int argc, char const *argv[]) {
    A<int> a;
    a.func('K');    // instantiate the member function template
    return 0;
}
