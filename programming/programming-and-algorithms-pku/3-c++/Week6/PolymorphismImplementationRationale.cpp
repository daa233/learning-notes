/**
 * @file: PolymorphismImplementationRationale.cpp
 * @description: 多态的实现原理
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

class Base {
public:
    int i;
    virtual void print() {
        cout << "Base::print" << endl;
    }
};

class Derived : public Base {
public:
    int n;
    virtual void print() {
        cout << "Derived:print" << endl;
    }
};

class BaseWithoutVirtualFunction {
public:
    int i;
    void someFunction() {}
};

class DerivedWithoutVirtualFunction : public BaseWithoutVirtualFunction {
public:
    int n;
    void someFunction() {}
};

int main(int argc, char const *argv[]) {
    Base b;
    Derived d;
    cout << "sizeof(int) = " << sizeof(int) << endl;        // 4
    cout << "sizeof(int *) = " << sizeof(int *) << endl;    // 8
    cout << sizeof(b) << ", " << sizeof(d) << endl;         // 16, 16
    BaseWithoutVirtualFunction bwovf;
    DerivedWithoutVirtualFunction dwovf;
    cout << sizeof(bwovf) << ", " << sizeof(dwovf) << endl;
    return 0;
}
