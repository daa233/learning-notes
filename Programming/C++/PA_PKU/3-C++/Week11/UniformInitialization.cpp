/**
 * @file: UniformInitialization.cpp
 * @description: C++11 新特性，统一的初始化方法
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct A {
    int i, j;
    A(int m, int n) : i(m), j(n) {}
};

A func(int m, int n) {
    return {m, n};      // not recommended
}

int main(int argc, char const *argv[]) {
    int arr[3]{1, 2, 3};
    vector<int> iv{1, 2, 3};
    map<int, string> mp{{1, "a"}, {2, "b"}};
    string str{"Hello world"};
    int *p = new int[20]{1, 2, 3};  // left elements are 0
    A *pa = new A{3, 7};
    delete pa;
    return 0;
}
