/**
 * 类和对象 编程题＃3
 *
 * @file: Week3Ex3.cpp
 * @description: 程序填空
 * @input:

 * @output: 
    5,5
    5,5
 * @sample_input:

 * @sample_output:
    5,5
    5,5
 *
 * @author: Du Ang
 * @date: Aug. 15th, 2017
 */

#include <iostream>
using namespace std;
class Base {
public:
    int k;
    Base(int n):k(n) { }
};
class Big  {
public:
    int v; Base b;
    // 在此处补充你的代码
    Big(int n) : v(5), b(5) {}
    Big(const Big &big) : v(big.v), b(big.b.k) {}
};
int main()  {
    Big a1(5);    Big a2 = a1;
    cout << a1.v << "," << a1.b.k << endl;
    cout << a2.v << "," << a2.b.k << endl;
    return 0;
}
