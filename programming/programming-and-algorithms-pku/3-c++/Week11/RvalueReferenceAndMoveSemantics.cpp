/**
 * @file: RvalueReferenceAndMoveSemantics.cpp
 * @description: C++11 新特性，右值引用和 move 语义
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 4th, 2017
 */

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class String {
public:
    char *str;
    String() : str(new char[1]) {
        str[0] = 0;
    }
    String(const char *s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    String(const String &s) {
        cout << "copy constructor is called" << endl;
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }
    String &operator=(const String &s) {
        cout << "copy operator= is called" << endl;
        if (str != s.str) {
            delete[] str;
            str = new char[strlen(s.str) + 1];
            strcpy(str, s.str);
        }
        return *this;
    }
    // move constructor
    String(String &&s) : str(s.str) {
        cout << "move constructor is called" << endl;
        s.str = new char[1];
        s.str[0] = 0;
    }
    // move assignment
    String &operator=(String &&s) {
        cout << "move operator= is called" << endl;
        if (str != s.str) { // check if it is self-assignment
            str = s.str;
            s.str = new char[1];
            s.str[0] = 0;
        }
        return *this;
    }
    ~String() {
        delete[] str;
    }
};

template <class T>
void MoveSwap(T &a, T &b) {
    // move() can return a rvalue, but a and b will be modified
    // use move when a and b are temporary variables
    T tmp(move(a));     // call move constructor here
    a = move(b);        // call move assignment here
    b = move(tmp);      // call move assignment here
}

int main(int argc, char const *argv[]) {
    // error: non-const lvalue reference to type 'String' cannot bind to a
    //   temporary of type 'String'
    // String &r = String("this");
    String s;
    s = String("this");         // move operator= is called
    cout << "*****" << endl;
    cout << s.str << endl;      // this
    String &&r = String("ok");
    cout << r.str << endl;      // ok
    cout << "******" << endl;
    String s1 = "hello";
    String s2 = "world";
    MoveSwap(s1, s2);
    // move constructor is called
    // move operator= is called
    // move operator= is called
    cout << s1.str << endl;     // world
    cout << s2.str << endl;     // hello
    return 0;
}
