/**
 * @file: MultiMapSample.cpp
 * @description: STL 中 multimap 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {
    typedef multimap<int, double, less<int> > mmid;
    mmid pairs;
    cout << "1) " << pairs.count(15) << endl;
    pairs.insert(mmid::value_type(15, 2.7));
    pairs.insert(mmid::value_type(15, 99.3));
    // get the number of the elements whose keys are 15
    cout << "2) " << pairs.count(15) << endl;
    pairs.insert(mmid::value_type(30, 111.11));
    pairs.insert(mmid::value_type(10, 22.22));
    pairs.insert(mmid::value_type(25, 33.333));
    pairs.insert(mmid::value_type(20, 9.3));
    // the keys of the elements are sorted from the smallest to the largest
    for (mmid::const_iterator i = pairs.begin(); i != pairs.end(); i++) {
        cout << "(" << i->first << ", " << i->second << ")" << ", ";
    }
    cout << endl;
    return 0;
}
