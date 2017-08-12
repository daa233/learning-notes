/**
 * @file: FunctionOverloading.cpp
 * @description: 内联函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

int Max(double f1, double f2) {}
int Max(int n1, int n2) {}
int Max(int n1, int n2, int n3) {}
// error: functions that differ only in their returntype cannot be overloaded
// double Max(double f1, double f2) {}

int main(int argc, char const *argv[]) {
    Max(3.4, 2.5);  // 调用 int Max(double f1, double f2)
    Max(2, 4);      // 调用 int Max(int n1, int n2)
    Max(1, 2, 3);   // 调用 int Max(int n1, int n2, int n3)
    // Max(3, 2.4);    // error: call to 'Max' is ambiguous
    return 0;
}
