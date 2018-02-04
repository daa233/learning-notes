/**
 * @file: MinElementMaxElementSample.cpp
 * @description: STL 中 min_element 和 max_element 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <algorithm>

using namespace std;

class A {
public:
    int n;
    A(int i) : n(i) {}
};

bool operator<(const A &a1, const A &a2) {
    cout << "< is called" << endl;
    // only 3 < 7 returns true
    if (a1.n == 3 && a2.n == 7) {
        return true;
    }
    return false;
}

int main(int argc, char const *argv[]) {
    A aa[] = {3, 5, 7, 2, 1};
    cout << min_element(aa, aa + 5)->n << endl;
    cout << max_element(aa, aa + 5)->n << endl;
    return 0;
}
