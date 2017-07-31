/**
 * @file: AutoOperation.cpp
 * @description: 自增、自减运算符
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int i = 3;
    cout << -i++ << endl;   // 输出结果为-3，运算后i为4
    i = 3;
    cout << -++i << endl;   // 输出结果为-4，运算后i为4
    // i = 3;
    // cout << (-i)++ << endl; // 错误，++/--运算只能用于变量，不能用于表达式
    // i = 3;
    // cout << ++i++ << endl;  // 错误，原因同上

    int a = 0, b = 0, c = 2, d = 0, e = 2, f = 2;
    // 注意：cout中包含多个表达式时，从右往左计算表达式的值
    cout << a << " " << a++ << " " << endl;     // 输出结果为：1 0
    cout << ++b << " " << b++ << " " << endl;   // 输出结果为：2 0
    cout << c << " " << (c++) + (++c) << endl;  // 输出结果为：4 6。表达式中有++c时，优先计算它。
    cout << (d = f++) + (e = f) << endl;        // gcc输出结果为：5. VC++输出结果为：4
    cout << f << " " << d << " " << e << endl;//gcc输出结果为：3 2 3. VC++输出结果为：3 2 2

    return 0;
}
