/**
 * @file: VirtualFucntionAndPolymorphism.cpp
 * @description: 虚函数和多态 多态函数的简单示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 23rd, 2017
 */

#include <iostream>

using namespace std;

class A {
public:
    virtual void print() {
        cout << "A::print" << endl;
    }
};

class B : public A {
public:
    virtual void print() {
        cout << "B::print" << endl;
    }
};

class D : public A {
public:
    virtual void print() {
        cout << "D::print" << endl;
    }
};

class E : public A {
    virtual void print() {
        cout << "E::print" << endl;
    }
};

int main(int argc, char const *argv[]) {
    A a;
    B b;
    D d;
    E e;
    A *pa = &a;
    B *pb = &b;
    D *pd = &d;
    E *pe = &e;

    pa->print();    // A::print
    pa = pb;
    pa->print();    // B::print
    pa = pd;
    pa->print();    // D::print
    pa = pe;
    pa->print();    // E::print

    return 0;
}
