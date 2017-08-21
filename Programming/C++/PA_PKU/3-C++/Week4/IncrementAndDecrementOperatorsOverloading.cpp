/**
 * @file: IncrementAndDecrementOperatorsOverloading.cpp
 * @description: 自加自减运算符的重载
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 21st, 2017
 */

#include <iostream>

using namespace std;

class CDemo {
private:
    int n;
public:
    CDemo(int i = 0) : n(i) {}
    CDemo &operator++();    // prefix increment
    CDemo operator++(int);  // postfix increment
    operator int() {        // int cast overloading
        // cout << "type cast to int" << endl;
        return n;
    }
    friend CDemo &operator--(CDemo &);      // prefix decrement
    friend CDemo operator--(CDemo &, int);  // postfix decrement
};

// prefix increment
CDemo &CDemo::operator++() {
    n++;
    return *this;
}

// postfix increment
CDemo CDemo::operator++(int k) {
    CDemo tmp(*this);
    n++;
    return tmp;
}

// prefix decrement
CDemo &operator--(CDemo &d) {
    d.n--;
    return d;
}

// postfix decrement
CDemo operator--(CDemo &d, int) {
    CDemo tmp(d);
    d.n--;
    return tmp;
}

int main(int argc, char const *argv[]) {
    CDemo d(5);
    cout << (d++) << ", ";  // automatically call int cast
    cout << d << ", ";
    cout << (++d) << ", ";
    cout << d << endl;
    cout << (d--) << ", ";
    cout << d << ", ";
    cout << (--d) << ", ";
    cout << d << endl;
    return 0;
}
