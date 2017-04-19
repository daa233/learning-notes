/** 习题课一：枚举、模拟与递归 编程题 #1
 * @file: SimplerBracketMatching.cpp
 * @description: 括号匹配简化版
 * 样例输入
    第一组
    (()()(()))
    第二组
    ((((())(())
 * 样例输出
    matched
    unmatched
 *
 * @author: Du Ang
 * @date: Apr. 18th, 2017
 */

#include <iostream>
#include <string.h> // strlen()

using namespace std;

/*  习题课学长的思路及实现
    匹配的括号 = (匹配的括号)匹配的括号
    bool, int = f(cahr str[], int s)
    f(str, s)代表从第s位置开始查验str中的括号是否匹配，如果查验已经覆盖整个字符串，且成功匹配，则返回(true, -1)；如果还没有查验完整个字
    符串，返回当前所查验的字符串是否匹配，并且返回当前所查验到的位置，如(true, index)或(false, index)。

bool b; // 全局变量b，作为f(char str[], int s)的一个返回值
int f(char str[], int s)
{
    if (strlen(str) == s) {     // 字符串已经查验到最后一位，匹配完成，返回(true, -1)
        return (b = true, -1);  // 利用逗号表达式完成多返回值函数，返回-1前对全局变量b进行赋值
    } else {    // 当前所需要查验的位置还不是字符串的最后一位
        if (str[s] == '(') {
            int n;
            (b, n) = f(str, s+1);   // 返回从第s+1位开始查验的结果
            if (!b) {   // f(str, s+1) unmatched
                return (b = false, n);
            } else {    // f(str, s+1) matched
                if (str[n] == ')')
                    return f(str, n+1);
                else
                    return (b = false, n);
            }
        } else {    // str[s] == ')'，默认为输入的字符不是'('，就是')'
            return (b = true, s);
        }
    }
}

int main(int argc, char *argv[])
{
    char s[100];
    cin >> s;
    int code;
    (b, code) = f(s, 0);
    if (b && code == -1) {
        cout << "matched" << endl;
    } else {
        cout << "unmatched" << endl;
    }
    return 0;
}
*/

/* 我的思路
    设 M 为任一括号匹配的字符串，分情况讨论：
    1. 匹配的情况: (M)M  返回 0
    2. 不匹配的情况:  a. M)M  返回 -1
                    b. M(M  返回  1
*/
int f(char str[], int start, int state);
// start表示查验字符串的起点;
// state表示start之前的字符串的查验结果状态值,匹配为0;多一个左括号为-1; 多一个右括号为1,此时肯定无法匹配.
int f(char str[], int start, int state)
{
    if (state <= 0) {
        if (strlen(str) == start) {
            return state;   // 已经查验完整个字符串,返回最后的状态值. 如果为0,表示匹配; 如果非0,表示不匹配.
        } else {            // 字符串还没有查验完成
            if (str[start] == '(') {    // 从start开始的字符串以'('开头
                return f(str, start + 1, state - 1);    // 返回查验start+1开始的字符串结果,其初始状态值-1.
            } else {
                return f(str, start + 1, state + 1);
            }
        }
    } else {
        return 1;
    }

}

int main(int argc, char *argv[])
{
    char str[100];
    cin >> str;
    int state = f(str, 0, 0);
    if (state == 0) {
        cout << "matched" << endl;
    } else {
        cout << "unmatched" << endl;
    }
    return 0;
}
