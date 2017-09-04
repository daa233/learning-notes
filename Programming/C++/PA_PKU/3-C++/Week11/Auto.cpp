/**
 * @file: Auto.cpp
 * @description: C++11 新特性，auto 关键字
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>
#include <map>

using namespace std;

class A {
    A operator+(int n, const A &a) {
        return a;
    }
};

template <class T1, class T2>
auto add(T1 x, T2 y) -> decltype(x + y) {   // return type depends on (x + y)
    return x + y;
}

int main(int argc, char const *argv[]) {
    auto i = 100;       // i is int
    auto p = new A();   // p is A *
    auto k = 34343LL;   // k is long long
    map<string, int, greater<string> > mp;
    for (auto i = mp.begin(); i != mp.end(); ++i) {
        // i is map<string, int, greater<string> >::iterator
        cout << i->first << ", " << i->second;
    }
    auto d = add(100, 1.5); // double d = 101.5
    auto f = add(100, A()); // the type of f is A
    return 0;
}
