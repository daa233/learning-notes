/**
 * @file: MapSample.cpp
 * @description: STL 中 map 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <map>

using namespace std;

template <class Key, class Value>
ostream &operator<<(ostream &o, const pair<Key, Value> &p) {
    o << "(" << p.first << ", " << p.second << ")";
    return o;
}

int main(int argc, char const *argv[]) {
    typedef map<int, double, less<int> > mmid;
    mmid pairs;
    cout << "1) " << pairs.count(15) << endl;
    // 1) 0
    pairs.insert(mmid::value_type(15, 2.7));
    pairs.insert(make_pair(15, 99.3));
    cout << "2) " << pairs.count(15) << endl;
    // 2) 1
    pairs.insert(mmid::value_type(20, 9.3));
    mmid::iterator i;
    cout << "3) ";
    for (i = pairs.begin(); i != pairs.end(); i++) {
        cout << *i << ", ";
    }
    // 3) (15, 2.7), (20, 9.3),
    cout << endl;
    cout << "4) ";
    int n = pairs[40];  // if there is no element whose first is 40, insert one
    for (i = pairs.begin(); i != pairs.end(); i++) {
        cout << *i << ", ";
    }
    // 4) (15, 2.7), (20, 9.3), (40, 0),
    cout << endl;
    cout << "5) ";
    pairs[15] = 628;    // find the element whose first is 15, set its second to 628
    for (i = pairs.begin(); i != pairs.end(); i++) {
        cout << *i << ", ";
    }
    // 5) (15, 628), (20, 9.3), (40, 0),
    cout << endl;
    return 0;
}
