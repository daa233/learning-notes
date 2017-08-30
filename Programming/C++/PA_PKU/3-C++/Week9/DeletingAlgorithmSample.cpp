/**
 * @file: DeletingAlgorithmSample.cpp
 * @description: STL 中 的删除算法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
    int a[5] = {1, 2, 3, 2, 5};
    int b[6] = {1, 2, 3, 2, 5, 6};
    ostream_iterator<int> oit(cout, ", ");
    int *p = remove(a, a + 5, 2);
    cout << "1) ";
    copy(a, a + 5, oit);
    // 1) 1, 3, 5, 2, 5,
    cout << endl;
    // print the number of the left elements
    cout << "2) " << p - a << endl;
    // 2) 3
    vector<int> v(b, b + 6);
    remove(v.begin(), v.end(), 2);
    cout << "3) ";
    copy(v.begin(), v.end(), oit);
    // 3) 1, 3, 5, 6, 5, 6,
    cout << endl;
    cout << "4) ";
    cout << v.size() << endl;
    return 0;
}
