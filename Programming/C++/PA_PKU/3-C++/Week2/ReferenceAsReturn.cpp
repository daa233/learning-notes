/**
 * @file: ReferenceAsReturn.cpp
 * @description: 引用作为函数的返回值
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

int n = 4;

int &setValue()
{
    return n;
}

int main(int argc, char const *argv[]) {
    setValue() = 40;
    cout << n << endl;
    return 0;
}
