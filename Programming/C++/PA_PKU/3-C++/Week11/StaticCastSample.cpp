/**
 * @file: StaticCastSample.cpp
 * @description: static_cast 示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>

using namespace std;

class A {
public:
    // no return value when overloading cast operator
    operator int() {    // overload int cast
        return 1;
    }
    operator char *() { // overload char * cast
        return NULL;
    }
};

int main(int argc, char const *argv[]) {
    A a;
    int n;
    char *p = "New Dragon Inn";
    n = static_cast<int>(3.14);
    cout << n << endl;          // 3
    n = static_cast<int>(a);
    cout << n << endl;          // 1
    p = static_cast<char *>(a); // call a.operator char *, set p to NULL
    // n = static_cast<int>(p);    // error: static_cast from 'char *' to 'int' is not allowed
    // p = static_cast<char *>(n); // error: cannot cast from type 'int' to pointer type 'char *'
    return 0;
}
