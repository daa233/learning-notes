/**
 * @file: MultiSetSample.cpp
 * @description: STL 中 set 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <set>

using namespace std;

template <class T>
void print(T first, T last) {
    for ( ; first != last; ++first) {
        cout << *first << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    typedef set<int>::iterator IT;
    int a[5] = {3, 4, 6, 1, 2};
    set<int> st(a, a + 5);
    print(st.begin(), st.end());
    pair<IT, bool> result;
    result = st.insert(5);
    if (result.second) {
        cout << *result.first << " inserted" << endl;
    } else {
        cout << "failed to insert " << *result.first << endl;
    }
    print(st.begin(), st.end());
    if (st.insert(5).second) {
        cout << *result.first << endl;
    } else {
        cout << *result.first << " already exists" << endl;
    }
    // equal_range: get lower_bound and upper_bound simultaneously
    pair<IT, IT> bounds = st.equal_range(4);
    cout << *bounds.first << ", " << *bounds.second << endl;
    return 0;
}
