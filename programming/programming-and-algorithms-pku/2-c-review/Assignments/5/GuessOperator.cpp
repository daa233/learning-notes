/**
 * 期末考试 编程题＃3：运算符判定（未在 OpenJudge 上找到对应题目）
 *
 * @file: GuessOperator.cpp
 * @description: 两个整数 a 和 b 运算后得到结果 c。表示为：a ? b = c，其中，？可能是加法 +，减法 -，乘法 *，
                整除 / 或 取余 %。请根据输入的 a, b, c 的值，确定运算符。如果某种运算成立，则输出相应的运算符，
                如果任何运算都不成立，则输出 error.
 * @input: a b 和 c 的值在意行内输入，以逗号间隔
 * @output: 五个运算符之一或 error
 * @sample_input:
    6,7,13
 * @sample_output:
    +
 *
 * @author: Du Ang
 * @date: Aug. 10th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int a, b, c;
    char dummy1, dummy2;
    cin >> a >> dummy1 >> b >> dummy2 >> c;

    // If more than one operators satisfy the condition, only print one here
    if (a + b == c) {
        cout << "+" << endl;
    } else if (a - b == c) {
        cout << "-" << endl;
    } else if (a * b == c) {
        cout << "*" << endl;
    } else if (a / b == c) {
        cout << "/" << endl;
    } else if (a % b == c) {
        cout << "%" << endl;
    } else {
        cout << "error" << endl;
    }
    return 0;
}
