/**
 * @file: DynamicCastSample.cpp
 * @description: dynamic_cast 示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

int main(int argc, char const *argv[]) {
    Base b;
    Derived d;
    Derived *pd;
    pd = reinterpret_cast<Derived *>(&b);           // always cast
    if (pd == NULL) {                               // pd is not NULL here
        cout << "unsafe reinterpret_cast" << endl;  // won't execute
    }
    pd = dynamic_cast<Derived *>(&b);
    if (pd == NULL) {
        cout << "unsafe dynamic_cast 1" << endl;    // unsafe dynamic_cast 1
    }
    Base *pb = &d;
    pd = dynamic_cast<Derived *>(pb);               // safe cast
    if (pd == NULL) {                               // pd is not NULL here
        cout << "unsafe dynamic_cast 2" << endl;    // won't execute
    }
    return 0;
}
