/**
 * @file: BadCastException.cpp
 * @description: bad_cast 示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>
#include <stdexcept>
#include <typeinfo>

using namespace std;

class Base {
    virtual void func() {}
};

class Derived : public Base {
public:
    void print() {}
};

void printObj(Base &b) {
    try {
        // if not safe, it will throw bad_cast
        Derived &rd = dynamic_cast<Derived &>(b);
        rd.print();
    } catch (bad_cast &e) {
        cerr << e.what() << endl;
    }
}

int main(int argc, char const *argv[]) {
    Base b;
    printObj(b);    // std::bad_cast
    return 0;
}
