/**
 * @file: SortSample.cpp
 * @description: STL 中 sort 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 31st, 2017
 */

#include <iostream>
#include <algorithm>

using namespace std;

class MyLess {
public:
    bool operator()(int n1, int n2) {
        return (n1 % 10) < (n2 % 10);
    }
};

int main(int argc, char const *argv[]) {
    int a[] = {14, 2, 9, 111, 78};
    sort(a, a + 5, MyLess());
    int i;
    for (i = 0; i < 5; i++) {
        cout << a[i] << " ";
    }
    // 111 2 14 78 9
    cout << endl;
    sort(a, a + 5, greater<int>());
    for (i = 0; i < 5; i++) {
        cout << a[i] << " ";
    }
    // 111 78 14 9 2
    cout << endl;
    return 0;
}
