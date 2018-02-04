/**
 * @file: DerivedClassConstructor.cpp
 * @description: 派生类对象的构造函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 22nd, 2017
 */

#include <iostream>

using namespace std;

class Bug {
private:
    int nLegs;
    int nColor;
public:
    int nType;
    Bug(int legs, int color);
    void printBug() {}
};

class FlyBug : public Bug {
    int nWings;
public:
    FlyBug(int legs, int color, int wings);
};

Bug::Bug(int legs, int color) {
    nLegs = legs;
    nColor = color;
}

/* wrong FlyBug constructor
FlyBug::FlyBug(int legs, int color, int wings) {
    nLegs = legs;       // error: 'nLegs' is a private member of 'Bug'
    nColor = color;     // error: 'nColor' is a private member of 'Bug'
    nType = 1;
    nWings = wings;
}
*/

// right FlyBug constructor
FlyBug::FlyBug(int legs, int color, int wings) : Bug(legs, color) {
    nWings = wings;
}


class Base {
public:
    int n;
    Base(int i) : n(i) {
        cout << "Base " << n << " constructed" << endl;
    }
    ~Base() {
        cout << "Base " << n << " destructed" << endl;
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

int main() {
    FlyBug fb(2, 3, 4);
    fb.printBug();
    fb.nType = 1;
    // fb.nLegs = 2;   // error: 'nLegs' is a private member of 'Bug'

    Derived obj(3);
    // Base 3 constructed
    // Derived constructed
    // Derived destructed
    // Base 3 destructed
    return 0;
}
