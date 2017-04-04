/**
 * 理性认识C程序  编程题 #4：最大奇数与最小偶数之差的绝对值
 *
 * @file: Abs.cpp
 * @description: 输入6个正整数，且这6个正整数中至少存在一个奇数和一个偶数。
                设这6个正整数中最大的奇数为a，最小的偶数为b，求出|a-b|的值
 * @input: 输入为一行，6个正整数,且6个正整数都小于100。输入保证这6个数中至少存在一个奇数和一个偶数
 * @output: 输出为一行，输出最大的奇数与最小的偶数之差的绝对值
 * 样例输入
    第一组
    1 2 3 4 5 6
    第二组
    1 6 3 8 5 10
 * 样例输出
    第一组
    3
    第二组
    1
 *
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int maxOdd;     // 用于存放最大的奇数
    int minEven;    // 用于存放最小的偶数
    int result;     // 用于存放最后的结果，最大的奇数与最小的偶数之差的绝对值
    bool oddInitFlag = false, evenInitFlag = false; // maxOdd和minEven的初始化标识
    // 找出maxOdd和minEven
    for (int i = 0; i < 6; i++) {
        int temp;   // 临时存放用户的输入
        cin >> temp;
        if (temp % 2 != 0) {
            // 用户的这个输入是个奇数
            if (!oddInitFlag) {
                // maxOdd还没有被初始化，则先初始化赋值
                maxOdd = temp;
                oddInitFlag = true;
            } else {
                // maxOdd已经初始化过，则和temp比较，大者赋给maxOdd
                maxOdd = temp > maxOdd ? temp : maxOdd;
            }
        } else {
            // 用户的这个输入是个偶数
            if (!evenInitFlag) {
                // minEven还没有被初始化，则先初始化赋值
                minEven = temp;
                evenInitFlag = true;
            } else {
                // minEven已经初始化过，则和temp比较，小者赋给minEven
                minEven = temp < minEven ? temp : minEven;
            }
        }
    }
    result = maxOdd - minEven;
    result = result > 0 ? result : -result;
    cout << result << endl;

    return 0;
}
