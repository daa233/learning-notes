/**
 * @file: ReversePolishNotation.cpp
 * @description: 逆波兰表达式是一种把运算符前置的算术表达式。如 2 + 3 的逆波兰表示法为 + 2 3。如 (2 + 3) * 4 的逆波
                兰表示法为 * + 2 3 4。
                编写程序求解任一仅包含+、-、*、/四个运算符的逆波兰表达式的值。
 * @input: 逆波兰表达式
 * @output: 运算结果
 * 样例输入：
    第一组
    * + 11 12 + 24 35
    第二组
    * / + 12 36 + 1 3 - 15 8
 * 样例输出：
    第一组
    1357.0
    第二组
    84
 *
 * @author: Du Ang
 * @date: Apr. 17th, 2017
 */

#include <iostream>
#include <cstdlib>  // To use double atof(double)

using namespace std;

/*
    注意：仅包含+、-、*、/四个运算符的逆波兰表达式的特点：1.如果包含运算符，一定以运算符开头； 2.任一运算符后都包含两个逆波兰表达式
    步骤：
    1. 假设 notation() 函数能够得到逆波兰表达式的值
    2. [operator] [part1] [part2] 会被 notation() 函数解析为 notation() [operator] notation()
    3. 最简单的情况就是逆波兰表达式为纯数字，直接返回数值即可
*/
double notation()
{
    char str[10];
    cin >> str; // cin每次从输入缓存区读取一个字符串，到空格截止
    switch (str[0]) {
        case '+': return notation() + notation();
        case '-': return notation() - notation();
        case '*': return notation() * notation();
        case '/': return notation() / notation();
        default:  return atof(str); // 数字
    }
}

int main(int argc, char const *argv[]) {
    cout << notation() << endl;
    return 0;
}
