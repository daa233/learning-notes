/**
 * 从现实问题到计算机程序  编程题 #3：整数的个数
 *
 * @file: IntegerNumbers.cpp
 * @description: 给定k（1<k<100）个正整数，其中每个数都是大于等于1，小于等于10的数。写程序计算给定的k个正整数中，1，5和10
                出现的次数。
 * @input: 输入有两行：第一行包含一个正整数k，第二行包含k个正整数，每两个正整数用一个空格分开。
 * @output: 输出有三行，第一行为1出现的次数，，第二行为5出现的次数，第三行为10出现的次数。
 * 样例输入
    第一组
    5
    1 5 8 10 5
    第二组
    5
    2 2 2 2 2
* 样例输出
    第一组
    1
    2
    1
    第二组
    0
    0
    0
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int k;  // 正整数的数目k
    int num; // 输入的正整数的值
    int cnt1 = 0, cnt5 = 0, cnt10 = 0;  // 分别用于记录1,5,10的个数
    cin >> k;   // 输入正整数的数目
    if (k > 1 && k < 100) { // 1 < k < 100
        for (int i = 0; i < k; i++) {
            cin >> num;
            if (num >= 1 && num <= 10) {
                switch (num) {
                    case 1:
                        cnt1++;
                        break;
                    case 5:
                        cnt5++;
                        break;
                    case 10:
                        cnt10++;
                        break;
                    default:
                        break;
                }
            } else {
                cout << "Error input! The range is 1 to 10(1 and 10 in).\n";
                return -1;
            }
        }

        // 输出结果
        cout << cnt1 << endl;
        cout << cnt5 << endl;
        cout << cnt10 << endl;
    } else {
        cout << "Error! Require 1 < k 100." << endl;
        return -1;
    }


    return 0;
}
