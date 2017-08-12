/**
 * @file: DefaultArguments.cpp
 * @description: 缺省参数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

void func(int x1, int x2 = 2, int x3 = 3) {}
// void func(int x1 = 1, int x2, int x3 = 3) {} // error: missing default argument on parameter 'x2'


int main(int argc, char const *argv[]) {
    func(10);       // OK, same as func(10, 2, 3);
    func(10, 8);    // OK, same as func(10, 8, 3);
    // func(10, , 8);  // error. 只能最右边的连续若干个参数缺省
    return 0;
}
