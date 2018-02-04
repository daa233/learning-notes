/**
 * @file: VectorSample.cpp
 * @description: vector 的用法示例
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
    int i;
    // 1D array
    cout << "1D array sample: " << endl;
    int a[5] = {1, 2, 3, 4, 5};
    vector<int> v(5);
    cout << v.end() - v.begin() << endl;
    for (i = 0; i < v.size(); i++) {
        v[i] = i;
    }
    v.at(4) = 100;
    for (i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
    vector<int> v2(a, a+5);
    v2.insert(v2.begin() + 2, 13);
    for (i = 0; i < v2.size(); i++) {
        cout << v2.at(i) << ", ";
    }
    cout << endl;

    // 2D dynamic array
    cout << "2D array sample: " << endl;
    vector< vector<int> > dv(3);
    // vector<vector<int>> dv(3);  // this may be -std=c++11 arg to pass compile
    for (int i = 0; i < dv.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            dv[i].push_back(i+j);
        }
    }
    for (int i = 0; i < dv.size(); ++i) {
        for (int j = 0; j < dv[i].size(); ++j) {
            cout << dv[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
