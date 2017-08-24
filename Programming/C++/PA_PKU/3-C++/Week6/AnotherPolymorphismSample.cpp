/**
 * @file: AnotherPolymorphismSample.cpp
 * @description: 更多多态程序实例——多态的又一例子
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 23rd, 2017
 */

#include <iostream>

using namespace std;

class Base {
public:
    void fun1() {
        // Call virtual function in a non-constructor and non-destructor function will invoke
        // polymorphism
        fun2();     // same as 'this->fun2();', this is a base pointer
    }
    virtual void fun2() {
        cout << "Base::fun2()" << endl;
    }
};

class Derived : public Base {
public:
    virtual void fun2() {
        cout << "Derived::fun2()" << endl;
    }
};

class Father {
public:
    virtual void hello() {
        cout << "Hello from Father." << endl;
    }
    virtual void bye() {
        cout << "Bye from Father." << endl;
    }
};

class Son : public Father {
public:
    Son() {hello();}    // hello is not polymorphism here
    ~Son() {bye();}     // derived bye() from base class Father
    // hello has the same virutal function name in base class, it's also virtual here
    void hello() {
        cout << "Hello from Son." << endl;
    }
};

class Grandson : public Son {
public:
    Grandson() {
        cout << "Constructing Grandson object" << endl;
    }
    ~Grandson() {
        cout << "Destructing Grandson object" << endl;
    }
    void hello() {  // virutal function
        cout << "Hello from Grandson" << endl;
    }
    void bye() {
        cout << "Bye from Grandson" << endl;
    }
};

int main(int argc, char const *argv[]) {
    Derived d;
    Base *pBase = &d;   // pBase is a pointer of base class, points to a object of derived class
    pBase->fun1();      // Derived::fun2()

    Grandson grandson;
    Son *son;
    son = &grandson;
    son->hello();       // polymorphism
    // Hello from Son.
    // Constructing Grandson object
    // Hello from Grandson
    // Destructing Grandson object
    // Bye from Father.
    return 0;
}
