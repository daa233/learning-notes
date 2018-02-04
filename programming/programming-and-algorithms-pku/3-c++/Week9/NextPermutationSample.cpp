/**
 * @file: NextPermutationSample.cpp
 * @description: STL 中 next_permutation 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 31st, 2017
 */

#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
    string str = "231";
    char szStr[] = "324";
    while (next_permutation(str.begin(), str.end())) {
        cout << str << endl;
    }
    // 312
    // 321
    cout << "****" << endl;
    while (next_permutation(szStr, szStr + 3)) {
        cout << szStr << endl;
    }
    // 342
    // 423
    // 432
    cout << "****" << endl;
    sort(str.begin(), str.end());
    cout << str << endl;
    // 123
    // if next pernext_permutation is "123"
    // next_permutation(str.begin(), str.end()) will return 0
    while (next_permutation(str.begin(), str.end())) {
        cout << str << endl;
    }
    // 132
    // 213
    // 231
    // 312
    // 321
    cout << "****" << endl;

    int a[] = {8, 7, 10};
    list<int> ls(a, a + 3);
    while (next_permutation(ls.begin(), ls.end())) {
        list<int>::iterator i;
        for (i = ls.begin(); i != ls.end(); ++i) {
            cout << *i << " ";
        }
        cout << endl;
    }
    // 8 10 7
    // 10 7 8
    // 10 8 7
    return 0;
}
