/**
 * @file: IteratorSample.cpp
 * @description: 迭代器示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 29th, 2017
 */

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    vector<int>::const_iterator i;
    for (i = v.begin(); i != v.end(); ++i) {
        cout << *i << ", ";
    }
    cout << endl;
    // 1, 2, 3, 4,

    vector<int>::reverse_iterator r;
    for (r = v.rbegin(); r != v.rend(); r++) {
        cout << *r << ", ";
    }
    cout << endl;
    // 4, 3, 2, 1,

    vector<int>::iterator j;
    for (j = v.begin(); j != v.end(); j++) {
        *j = 100;
    }

    for (i = v.begin(); i != v.end(); i++) {
        cout << *i << ", ";
    }
    cout << endl;
    // 100, 100, 100, 100,

    return 0;
}
