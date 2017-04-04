/**
 * 从现实问题到计算机程序  编程题 #2：奇数求和
 *
 * @file: OddSum.cpp
 * @description: 计算正整数 m 到 n（包括m 和 n ）之间的所有奇数的和，其中，m 不大于 n，且n 不大于300。
                例如 m=3, n=12, 其和则为：3+5+7+9+11=35
 * @input: 两个数 m 和 n，两个数以空格间隔，其中 0<=m <= n <= 300 。
 * @output: 奇数之和
 * 样例输入
    第一组
    7 15
    第二组
    0 1
    第三组
    3 3
    第四组
    100 100
 * 样例输出
    第一组
    55
    第二组
    1
    第三组
    3
    第四组
    0
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int m, n;   // m, n用于存放用户输入
    int sum = 0;    // sum用于存放所有奇数的和

    cin >> m >> n;
    if (m <= n && m >= 0 && n <= 300) {
        for (int i = m; i < n+1; i++) {
            if (i % 2 != 0) {
                sum = sum + i;
            }
        }
        cout << sum << endl;
    } else {
        cout << "Error input! m and n should be positive integers"
            << "between 1 and 300." << endl;
        cout << "What's more, m(first) should be smaller than n." << endl;
    }
    return 0;
}
