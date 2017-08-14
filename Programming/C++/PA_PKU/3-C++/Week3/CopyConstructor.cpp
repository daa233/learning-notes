/**
 * @file: CopyConstructor.cpp
 * @description: 复制构造函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 13th, 2017
 */

#include <iostream>

using namespace std;

class Complex {
private:
    double real;
    double imag;
public:
    Complex() {}    // 复制构造函数也是构造函数，一旦定义了，默认的无参构造函数会消失
    Complex(const Complex &c) {
        real = c.real;
        imag = c.imag;
        cout << "Complex copy constructor is called." << endl;
    }
};

class A {
public:
    A() {};
    A(A &a) {
        cout << "A copy constructor is called." << endl;
    }
};

void Func1(A a1) {}

class B {
public:
    int v;
    B(int n) {v = n;}
    B(const B &a) {
        v = 5;
        cout << "B copy constructor is called." << endl;
    }
};

B Func2() {
    B b(4);
    return b;
}

int main(int argc, char const *argv[]) {
    Complex c1;     // 调用自定义无参构造函数
    Complex c2(c1); // 调用自定义的复制构造函数
    // Complex copy constructor is called.

    A a2;
    Func1(a2);   // 由于是自定义复制构造函数，实参 a2 和形参 a1 不一定相等
    // A copy constructor is called.

    cout << Func2().v << endl;
    // B copy constructor is called.
    // 5
    // Note: If compile with G++, add `-fno-elide-constructors` argument
    return 0;
}
