/**
 * 理性认识C程序  编程题 #3：最高的分数
 *
 * @file: TopScore.cpp
 * @description: 孙老师讲授的《计算概论》这门课期中考试刚刚结束，他想知道考试中取得的最高分数。因为人数比较多，他觉得这件事情交给计算机来做
                比较方便。你能帮孙老师解决这个问题吗？
 * @input: 输入两行，第一行为整数n（1 <= n < 100），表示参加这次考试的人数.第二行是这n个学生的成绩，相邻两个数之间用单个空格隔开。所
        有成绩均为0到100之间的整数。
 * @output: 输出一个整数，即最高的成绩
 * 样例输入
    5
    85 78 90 99 60
 * 样例输出
    99
 *
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;  // 成绩总数
    int max;    // 最高的成绩
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;   // 用于存放用户输入的成绩
        cin >> temp;
        if (i == 0) max = temp; // 将max初始化为首个成绩
        max = temp > max ? temp : max;  // 比较temp和max的大小，大者赋值给max
    }
    cout << max << endl;
    return 0;
}
