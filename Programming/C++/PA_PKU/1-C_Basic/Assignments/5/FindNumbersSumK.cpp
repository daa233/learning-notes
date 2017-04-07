/**
 * C语言中的运算成分 逻辑运算应用练习 综合练习（2）#4：找和为K的两个元素
 *
 * @file: FindNumbersSumK.cpp
 * @description: 在一个长度为n(n < 1000)的整数序列中，判断是否存在某两个元素之和为k。
 * @input: 第一行输入序列的长度n和k，用空格分开。第二行输入序列中的n个整数，用空格分开。
 * @output: 如果存在某两个元素的和为k，则输出yes，否则输出no。
 * 样例输入
    9 10
    1 2 3 4 5 6 7 8 9
 * 样例输出
    yes
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n, k;
    cin >> n >> k;
    int num[n];     // 用于存放用户输入的n个数
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (num[i] + num[j] == k) {
                cout << "yes" << endl;  // 可以找到相加为k的两个数
                return 0;
            }
        }
    }
    cout << "no" << endl;   // 找不到能相加为k的两个数
    
    return 0;
}
