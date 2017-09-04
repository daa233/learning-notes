/**
 * @file: RangeBasedForLoop.cpp
 * @description: C++11 新特性，基于范围的 for 循环
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 4th, 2017
 */

#include <iostream>
#include <vector>

using namespace std;

struct A {
    int n;
    A(int i) : n(i) {}
};

int main(int argc, char const *argv[]) {
    int array[] = {1, 2, 3, 4, 5};
    for (int & e: array) {
        e *= 10;
    }
    for (int e : array) {
        cout << e << ", ";
    }
    // 10, 20, 30, 40, 50,
    cout << endl;
    vector<A> st(array, array + 5);
    for (auto & it : st) {
        it.n *= 10;
    }
    for (A it : st) {
        cout << it.n << ", ";
    }
    // 100, 200, 300, 400, 500,
    cout << endl;
    return 0;
}
