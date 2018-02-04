/**
 * @file: TraverseContainer.cpp
 * @description: 通过迭代器遍历各种容器
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 29th, 2017
 */

#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main(int argc, char const *argv[]) {
    // traverse vector
    cout << "Traverse vector: " << endl;
    vector<int> v(100);
    int i;
    for (i = 0; i < v.size(); i++) {
        v[i] = i;
        cout << v[i] << " ";   // randomly access by subscript
    }
    cout << endl;

    vector<int>::const_iterator ii;
    for(ii = v.begin(); ii != v.end(); ii++) {
        cout << *ii << " ";
    }
    cout << endl;

    for (ii = v.begin(); ii < v.end(); ii++) {
        cout << *ii << " ";
    }
    cout << endl;

    ii = v.begin();
    while (ii < v.end()) {
        cout << *ii << " ";
        ii = ii + 2;
    }
    cout << endl;


    // traverse list
    cout << "Traverse list: " << endl;
    list<int> l(100);
    list<int>::const_iterator iter;
    for (iter = l.begin(); iter != l.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
    // wrong, bidirectional iterators don't support <.
    // for (iter = l.begin(); iter < l.end(); ++iter) {
    //     cout << *iter;
    // }

    // wrong, list doesn't have [] member function
    // for (int iter = 0; iter < l.size(); iter++) {
    //     cout << l[iter];
    // }


    return 0;
}
