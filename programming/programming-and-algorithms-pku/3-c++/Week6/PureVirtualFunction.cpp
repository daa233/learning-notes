/**
 * @file: PureVirtualFunction.cpp
 * @description: 纯虚函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

class A {
public:
    virtual void f() = 0;
    void g() {
        this->f();
    }
    // A() {f();}   // error: Pure virtual function called!
};

class B : public A {
public:
    void f() {
        cout << "B::f()" << endl;
    }
};

int main(int argc, char const *argv[]) {
    B b;
    b.g();
    // B::f()
    return 0;
}
