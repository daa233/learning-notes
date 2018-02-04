/**
 * @file: OrderInterval.cpp
 * @description: STL 中 binary_search 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 31st, 2017
 */

#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>
#include <list>
#include <algorithm>

using namespace std;

bool greater10(int n) {
    return n > 10;
}

int main(int argc, char const *argv[]) {
    const int SIZE = 10;
    int a1[] = {2, 8, 1, 50, 3, 100, 8, 9, 10, 2};
    vector<int> v(a1, a1 + SIZE);
    ostream_iterator<int> output(cout, " ");
    vector<int>::iterator location;
    location = find(v.begin(), v.end(), 10);
    if (location != v.end()) {
        cout << "1) " << location - v.begin() << endl;
    }
    location = find_if(v.begin(), v.end(), greater10);
    if (location != v.end()) {
        cout << "2) " << location - v.begin() << endl;
    }
    sort(v.begin(), v.end());
    // binary_search need the elements sorted
    if (binary_search(v.begin(), v.end(), 9)) {
        cout << "3) " << "9 found" << endl;
    }
    return 0;
}
