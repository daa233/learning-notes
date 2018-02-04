/**
 * 从现实问题到计算机程序  编程题 #5: 数组逆序重放
 *
 * @file: ReverseArray.cpp
 * @description: 将一个数组中的值按逆序重新存放。例如，原来的顺序为8,6,5,4,1。要求改为1,4,5,6,8。
 * @input: 输入为两行：第一行数组中元素的个数n（1<n<100)，第二行是n个整数，每两个整数之间用空格分隔。
 * @output: 输出为一行：输出逆序后数组的整数，每两个整数之间用空格分隔。
 * 样例输入
    5
    8 6 5 4 1
 * 样例输出
    1 4 5 6 8
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int a[100];     // 数组
    int n;          // 数组中元素的个数 1 < n < 100
    cin >> n;
    if (n > 1 && n < 100) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        /*
        // 方法1：不改变数组本身，仅倒序输出
        for (int i = n-1; i >= 0; i--) {
            cout << a[i] << " ";
        }
        cout << endl;
        */

        // 方法2：将数组中的数逆序存放
        for (int i = 0; i < n / 2; i++) {
            int temp = a[i];    // 交换第i个和第n-1-i个位置的值
            a[i] = a[n-1-i];
            a[n-1-i] = temp;
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Error input. Require 1 < n < 100." << endl;
        return -1;
    }
    return 0;
}
