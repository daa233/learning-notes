/**
 * @file: VirtualDestructor.cpp
 * @description: 虚析构函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

class CSon {
public:
    virtual ~CSon() {
        cout << "Bye CSon." << endl;
    }
};

class CGrandson : public CSon {
public:
    ~CGrandson() {
        cout << "Bye CGrandson" << endl;
    }
};

int main() {
    CSon *p = new CGrandson;
    delete p;
    // Bye CGrandson
    // Bye CSon.
    return 0;
}
