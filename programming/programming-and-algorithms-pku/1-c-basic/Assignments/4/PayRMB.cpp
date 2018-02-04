/**
 * C语言中的数据成分 综合练习（1）编程题 #4：人民币支付
 *
 * @file: PayRMB.cpp
 * @description: 从键盘输入一指定金额（以元为单位，如345），然后输出支付该金额的各种面额的人民币数量，显示100元，50元，20元，
                10元，5元，1元各多少张，要求尽量使用大面额的钞票。
 * @input: 一个小于1000的正整数。
 * @output: 输出分行，每行显示一个整数，从上到下分别表示100元，50元，20元，10元，5元，1元人民币的张数
 * 样例输入
    735
 * 样例输出
    7
    0
    1
    1
    1
    0
    *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int money;  // 金额
    int num[6] = {0, 0, 0, 0, 0, 0};  // num[]用于存放各种面额钱的张数，num[5]对应100元

    cin >> money;   // 用户输入指定金额
    num[5] = money / 100;   // 100元的张数
    money = money - 100 * num[5];
    num[4] = money / 50;    // 50元的张数
    money = money - 50 * num[4];
    num[3] = money / 20;    // 20元的张数
    money = money - 20 * num[3];
    num[2] = money / 10;    // 10元的张数
    money = money - 10 * num[2];
    num[1] = money / 5;     // 5元的张数
    money = money - 5 * num[1];
    num[0] = money;         // 1元的张数
    // 打印出结果，从num[5]开始打印
    for (int i = 5; i >= 0; i--) {
        cout << num[i] << endl;
    }

    return 0;
}
