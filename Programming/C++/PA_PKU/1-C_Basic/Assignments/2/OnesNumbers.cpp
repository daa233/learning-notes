/**
 * 从现实问题到计算机程序  编程题 #4：1的个数
 *
 * @file: OnesNumbers.cpp
 * @description: 给定一个十进制整数，求其对应2进制数中1的个数
 * @input: 第一个整数表示有N组测试数据，其后N行是对应的测试数据，每行为一个整数。
 * @output: N行，每行输出对应一个输入。
 * 样例输入
     5
     2
     100
     1000
     66
     0
* 样例输出
    1
    3
    6
    2
    0
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int N;  // 测试数据组数为N
    int x;  // 用于记录每组测试数据
    int count; // 用于记录1的个数

    cin >> N;   // 输入测试组数N
    for (int i = 0; i < N; i++) {
        count = 0; // 计数清零
        cin >> x;   // 输入测试数据
        for ( ; ; x = x / 2) {    // 重复除以2求余数
            count = count + x % 2;
            if (x / 2 == 0) break;  // 为了把商一直除到0，将判断语句放在后面
        }
        cout << count << endl;
    }
    return 0;
}
