/**
 * @file: DirectAndIndirectClass.cpp
 * @description: 直接基类和间接基类
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 22nd, 2017
 */

#include <iostream>

using namespace std;

class Base {
public:
    int n;
    Base(int i) : n(i) {
        cout << "Base " << n << " constructed" << endl;
    }
    ~Base() {
        cout << "Base " << n << " constructed" << endl;
    }
};

class Derived : public Base {
public:
    Derived(int i) : Base(i) {
        cout << "Derived constructed" << endl;
    }
    ~Derived() {
        cout << "Derived destructed" << endl;
    }
};

class MoreDerived : public Derived {
public:
    MoreDerived() : Derived(4) {
        cout << "MoreDerived constructed" << endl;
    }
    ~MoreDerived() {
        cout << "MoreDerived destructed" << endl;
    }
};

int main() {
    MoreDerived obj;
    // Base 4 constructed
    // Derived constructed
    // MoreDerived constructed
    // MoreDerived destructed
    // Derived destructed
    // Base 4 constructed
    return 0;
}
