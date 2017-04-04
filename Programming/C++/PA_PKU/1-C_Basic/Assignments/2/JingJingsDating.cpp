/**
 * 从现实问题到计算机程序  编程题 #1：晶晶赴约会
 *
 * @file: JingJingsDating.cpp
 * @description: 晶晶的朋友贝贝约晶晶下周一起去看展览，但晶晶每周的1、3、5有课必须上课。
                请帮晶晶判断她能否接受贝贝的邀请，如果能输出YES；如果不能则输出NO。
 * @input: 输入有一行，贝贝邀请晶晶去看展览的日期，用数字1到7表示从星期一到星期日。
 * @output: 输出有一行，如果晶晶可以接受贝贝的邀请，输出YES，否则，输出NO。注意YES和NO都是大写字母！
 * 样例输入
    第一组
    1
    第二组
    2
    第三组
    3
 * 样例输出
    第一组
    NO
    第二组
    YES
    第三组
    NO
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int date;   // 贝贝邀请的日期
    cin >> date;
    if (date >= 1 && date <= 7) {
        if (date == 1 || date == 3 || date == 5) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    } else {
        cout << "Error input! That should be a number between 1 and 7.\n";
    }

    return 0;
}
