/**
 * @file: ConstructorAndDestructorExample.cpp
 * @description: 构造函数和析构函数调用时机的例题
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 14th, 2017
 */

#include <iostream>

using namespace std;

class Demo {
private:
    int id;
public:
    Demo(int i) {
        id = i;
        cout << "id = " << id << " constructor is called." << endl;
    }
    ~Demo() {
        cout << "id = " << id << " destructor is called." << endl;
    }
};

Demo d1(1); // global variable
// id = 1 constructor is called.

void Func() {
    static Demo d2(2);  // static variable
    // id = 2 constructor is called.
    Demo d3(3);
    // id = 3 constructor is called.
    cout << "Func ends." << endl;
    // id = 3 destructor is called.
}

int main(int argc, char const *argv[]) {
    Demo d4(4);
    // id = 4 constructor is called.
    d4 = 6; // id = 6 constructor is called.
    // id = 6 destructor is called.
    cout << "main starts." << endl;
    { // the start of Demo d5's scope of effect (作用域)
        Demo d5(5);
        // id = 5 constructor is called.
    } // the end of Demo d5's scope of effect
    // id = 5 destructor is called.
    Func();
    cout << "main ends." << endl;
    // id = 6 destructor is called. // Note: It is d4!
    // id = 2 destructor is called.
    // id = 1 destructor is called.

    return 0;
}
