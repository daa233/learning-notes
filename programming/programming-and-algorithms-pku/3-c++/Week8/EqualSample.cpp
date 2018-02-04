/**
 * @file: EqualSample.cpp
 * @description: STL 中“相等”概念演示
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 29th, 2017
 */

#include <iostream>

using namespace std;

class A {
private:
    int v;
public:
    A(int n) : v(n) {}
    bool operator<(const A &a2) const { // any object of class won't be smaller than the other
        cout << v << "<" << a2.v << "?" << endl;
        return false;
    }
    bool operator==(const A &a2) const {
        cout << v << "==" << a2.v << "?" << endl;
        return v == a2.v;
    }
};

int main(int argc, char const *argv[]) {
    A a[] = {A(1), A(2), A(3), A(4), A(5)};
    // if a < b return false, and b < a return false
    // then binary_search considers a is equal to b.
    cout << binary_search(a, a+4, A(9)) << endl;
    // 3<9?
    // 2<9?
    // 1<9?
    // 9<1?
    // 1
    return 0;
}
