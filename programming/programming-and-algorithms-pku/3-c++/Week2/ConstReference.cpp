/**
 * @file: ConstReference.cpp
 * @description: 常引用
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int n = 100;
    const int &r = n;
    // r = 200; // error: cannot assign to variable 'r' with const-qualified type 'const int &'
    n = 300;    // right
    cout << n << endl;  // 300
    return 0;
}
