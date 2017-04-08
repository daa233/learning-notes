/**
 * C语言中的数据成分 综合练习（1）编程题 #3：找出第k大的数
 *
 * @file: FindKthLargeNumber.cpp
 * @description: 用户输入N和K，然后接着输入N个正整数（无序的），程序在不对N个整数排序的情况下，找出第K大的数。
                注意，第K大的数意味着从大到小排在第K位的数。
 * @input:
    N
    K
    a1 a2 a3 a4 ..... aN
 * @output: b
 * 样例输入
    5
    2
    32 3 12 5 89
 * 样例输出
    32
 * @hint: 这是一道很经典的算法问题，是公司面试的常见考题。以后学习递归之后再回头看看这道题，或许有新解法。
 * @attention(add by me): 利用子函数findMinIndex(int a[], int length)时，
                        出现了Segmentation fault (core dumped)错误，回头再看
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;      // 共n个数
    int k;      // 找到第k大数
    int num[n]; // 存放用户输入的ｎ个数
    int max[k]; // 存放前k个最大的数

    cin >> n >> k;  // 用户输入n和k
    for (int i = 0; i < n; i++) {
        cin >> num[i];  // 用户输入ｎ个数
        if (i < k) {
            max[i] = num[i];    // 将max初始化为前k个输入的数
        }
    }
    // 从第k+1个数开始，将num中的数依次与max中的数比较，如果num中的数小于max中的每一个数，则max保持不变；否则，替换掉max中最小的数
    for (int i = k; i < n; i++) {
        for (int j = 0; j < k; j++) {
            // 如果num[i] > max[j]，用num[i]替换掉目前max[]中最小的数
            if (num[i] > max[j]) {
                // 寻找此时max[]中最小的值tempMin及其索引tempMinIndex
                int tempMin = max[0];   // 用于存储此时max[]中的最小值
                int tempMinIndex = 0;  // 用于存储此时max[]中最小值的索引
                // 找到max[]此时最小值的索引
                for (int l = 1; l < k; l++) {
                    // 如果tempMin大于max[i]，更新tempMin和tempMinIndex为max[i]和i
                    if (tempMin > max[l]) {
                        tempMin = max[l];
                        tempMinIndex = l;
                    }
                }
                max[tempMinIndex] = num[i];     // 用num[i]更新max[]中的最小值
                break;  // 退出本次循环，比较num[]中的下一个数
            }
        }
    }
    // 循环结束后，max[]存放着num[]中最大的k个数，其中最小的即为第k大的数
    int min = max[0];   // 用于存储此时max[]中的最小值
    int minIndex = 0;   // 用于存储此时max[]中最小值的索引
    // 找到max[]此时最小值的索引
    for (int i = 1; i < k; i++) {
        // 如果tempMin小于max[i]，更新tempMin和tempMinIndex为max[i]和i
        if (min > max[i]) {
            min = max[i];
            minIndex = i;
        }
    }
    cout << min << endl;  // 输出max中最小的数，即第k大的数

    return 0;
}
