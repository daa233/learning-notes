/**
 * @file: Destructor.cpp
 * @description: 析构函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 14th, 2017
 */

#include <iostream>

using namespace std;

class String {
private:
    char *p;
public:
    String() {
        p = new char[10];
    }
    ~String();
};

String::~String() {
    delete[] p;
}

class Ctest {
public:
    ~Ctest() {
        cout << "Destructor of Ctest is called" << endl;
    }
};

int main(int argc, char const *argv[]) {
    Ctest array[2];

    Ctest *pTest;
    pTest = new Ctest;
    delete pTest;
    // Destructor of Ctest is called

    cout << "End main" << endl;
    // End main
    // Destructor of Ctest is called
    // Destructor of Ctest is called
    return 0;
}
