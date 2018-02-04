/**
 * @file: AlgorithmSampleFind.cpp
 * @description: 算法示例 find()
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 29th, 2017
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
    int array[10] = {10, 20, 30, 40};
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    vector<int>::iterator p;
    p = find(v.begin(), v.end(), 3);
    if (p != v.end()) {
        cout << *p << endl;             // 3
    }
    p = find(v.begin(), v.end(), 9);
    if (p == v.end()) {
        cout << "not found" << endl;    // not found
    }
    p = find(v.begin() + 1, v.end() - 2, 1);    // search range [2, 3)
    if (p != v.end()) {
        cout << *p << endl;             // 3
    }

    int *pp = find(array, array + 4, 20);       // array name as iterator
    cout << *pp << endl;

    pp = find(array, array + 4, 15);
    cout << *pp << endl;                        // 0
    if ((array + 4) == pp) {
        cout << "now pp points to array[4]" << endl;

    }
    // now pp points to array[4]
    return 0;
}
