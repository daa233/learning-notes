/**
 * 理性认识C程序  编程题 #1：苹果和虫子
 *
 * @file: AppleAndWorms.cpp
 * @description: 你买了一箱n个苹果，很不幸的是买完时箱子里混进了一条虫子。虫子每x小时能吃掉一个苹果，假设虫子在吃完一个苹果之前不会吃另一
                个，那么经过y小时你还有多少个完整的苹果？
 * @input: 输入仅一行，包括n，x和y（均为整数）。
 * @output: 输出也仅一行，剩下的苹果个数
 * 样例输入
    第一组
    10 4 9
    第二组
    10 4 36
    第三组
    10 4 100
 * 样例输出
    第一组
    7
    第二组
    1
    第三组
    0
 * 提示：注意：是要求完整的苹果数。
 *
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;  // 苹果总数n
    int x;  // 虫子每x个小时吃一个苹果
    int y;  // 经过的时间y小时
    int remain; // 剩余完整苹果数

    cin >> n >> x >> y; // 获得输入
    int part = (y % x == 0) ? 0 : 1;    // 如果虫子刚好吃了整数个，则part为0；否则part为1。
    remain = n - y / x - part;
    if (remain < 0) remain = 0;         // 表示苹果早就被虫子吃完了
    cout << remain << endl;

    return 0;
}
