/**
 * @file: MemberVariableDefaultValue.cpp
 * @description: C++11 新特性，成员变量默认初始值
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>

using namespace std;

class B {
public:
    int m = 1234;
    int n;
};

int main(int argc, char const *argv[]) {
    B b;
    cout << b.m << endl;    // 1234
    return 0;
}
