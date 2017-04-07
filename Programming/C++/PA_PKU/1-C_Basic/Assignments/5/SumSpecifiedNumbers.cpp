/**
 * C语言中的运算成分 逻辑运算应用练习 综合练习（2）#1：数字求和
 *
 * @file: RacingComments.cpp
 * @description: 给定一个正整数a，以及另外的5个正整数，问题是：这5个整数中，小于a的整数的和是多少？
 * @input: 输入一行，只包括6个小于100的正整数，其中第一个正整数就是a。
 * @output: 输出一行，给出一个正整数，是5个数中小于a的数的和。
 * 样例输入
    10 1 2 3 4 11
 * 样例输出
    10
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int num[6];     // 存放输入的6个数
    int sum = 0;    // 存放最后的和
    for (int i = 0; i < 6; i++) {
        cin >> num[i];
        if (i >= 1 && num[i] < num[0]) {
            sum = sum + num[i];     // 如果num[i]比num[0]小，加到sum中
        }
    }
    cout << sum << endl;    // 打印sum
    return 0;
}
