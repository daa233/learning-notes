/**
 * 递归编程练习 编程题 #4：括号匹配问题（OpenJudge上搜“扩号匹配”，“扩”应为错别字）
 *
 * @file: BracketMatching.cpp
 * @description: 在某个字符串（长度不超过100）中有左括号、右括号和大小写字母；规定（与常见的算数式子一样）任何一个左括号都从内到外与在它
                右边且距离最近的右括号匹配。写一个程序，找到无法匹配的左括号和右括号，输出原来字符串，并在下一行标出不能匹配的括号。不能匹
                配的左括号用"$"标注,不能匹配的右括号用"?"标注.
 * @input: 输入包括多组数据，每组数据一行，包含一个字符串，只包含左右括号和大小写字母，字符串长度不超过100
            注意：cin.getline(str,100)最多只能输入99个字符！
 * @output: 对每组输出数据，!!!输出两行，第一行包含原始输入字符!!!，第二行由"$","?"和空格组成，"$"和"?"表示与之对应的左括号和右
            括号不能匹配。
 * 样例输入
((ABCD(x)
)(rttyy())sss)(
 * 样例输出
    ((ABCD(x)
    $$
    )(rttyy())sss)(
    ?            ?$
 *
 * @author: Du Ang
 * @date: Apr. 20th, 2017
 */

#include <iostream>
#include <string.h>

using namespace std;

int f(char str[], int index, int state)
{
    if (strlen(str) <= index) {
        return -1;
    } else {
        if (str[index] == '(') {
            int girlIndex = f(str, index+1, state-1);   // 尝试寻找下一个能匹配的右括号的位置
            if (girlIndex > 0) {    // 的确存在匹配的右括号，将其中匹配的左括号置为' '
                str[index] = ' ';
                return f(str, girlIndex+1, state);  // 从匹配的右括号下一位置继续查验
            } else {
                str[index] = '$';   // 不存在匹配的右括号，返回-1， 并将此左括号置为'$'
                return -1;
            }
        } else if (str[index] == ')') {
            if (state < 0) {    // 存在可以匹配的左括号，返回当前位置，并将当前位置置为' '
                str[index] = ' ';
                return index;
            } else {            // 不存在可以匹配的左括号，将当前位置替换为'?'，并继续查验下一位置
                str[index] = '?';
                f(str, index+1, state);
            }
        } else {
            str[index] = ' ';   // 当前位置为字母，替换为' '，并继续查验下一位置
            return f(str, index+1, state);
        }
    }
}

int main(int argc, char const *argv[]) {
    char str[100];
    while (true) {
        cin.getline(str, 101);
        if (strlen(str) == 0) return 0; // 没有输入内容，退出程序
        cout << str << endl;
        f(str, 0, 0);
        cout << str << endl;
    }
    return 0;
}
