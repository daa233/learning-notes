/**
 * @file: CheckOperatorPrecedence.cpp
 * @description: 验证包含逻辑运算符的混合运算的优先级
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int a = 0, b = 0;
    a = 5 > 3 && 2 || 8 < 4 - (b = !0);
    cout << a << " " << b << endl;  // 输出结果为：1 0
    // 注意：逻辑表达式求解中，并不总是执行所有的运算。只有在必须执行下一个逻辑运算符才能求出表达式的解时，才能执行该运算符。

    a = 0; b = 1;
    a = 8 > 4 - (b = !'c') && 5 > 3 + 'a' % 6 == 'b';
    cout << a << " " << b << endl;  // 输出结果：0 0

    a = 1; b = 2;
    int i = 0, c = 3;
    i = ++a || ++b || c++;
    cout << i << " " << a << " " << b << " " << c << endl;  // 输出结果：1 2 2 3

    return 0;
}
