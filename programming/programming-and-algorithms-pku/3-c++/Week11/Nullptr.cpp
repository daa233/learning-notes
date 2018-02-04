/**
 * @file: Nullptr.cpp
 * @description: C++11 新特性，空指针 nullptr
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 4th, 2017
 */

#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char const *argv[]) {
    int *p1 = NULL;
    int *p2 = nullptr;
    shared_ptr<double> p3 = nullptr;
    if (p1 == p2) {
        cout << "p1 equals p2" << endl;
        // p1 equals p2
    }
    if (p3 == nullptr) {
        cout << "p3 equals nullptr" << endl;
        // p3 equals nullptr
    }
    // error: invalid operands to binary expression ('int *' and 'shared_ptr<double>')
    // if (p2 == p3) {
    //     cout << "p2 equals p3" << endl;
    // }
    if (p3 == NULL) {
        cout << "p3 equals NULL" << endl;
        // p3 equals NULL
    }
    bool b = nullptr;   // b = false
    // error: cannot initialize a variable of type 'int' with an rvalue of type 'nullptr_t'
    // int i = nullptr;
    return 0;
}
