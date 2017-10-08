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
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

// minIndexMinVal[0] is the index of the min of max; minIndexMinVal[1] is the min value of max
int minIndexMinVal[2] = {0};

void findMinInMax(int a[], int length) {
    minIndexMinVal[0] = 0;
    minIndexMinVal[1] = a[0];
    for (int i = 1; i < length; i++) {
        if (minIndexMinVal[1] > a[i]) {
            minIndexMinVal[1] = a[i];
            minIndexMinVal[0] = i;
        }
    }
}

int main(int argc, char *argv[])
{
    int n;      // 共n个数
    int k;      // 找到第k大数
    cin >> n >> k;  // 用户输入n和k
    int num[n]; // 存放用户输入的ｎ个数
    int max[k]; // 存放前k个最大的数

    for (int i = 0; i < n; i++) {
        cin >> num[i];  // 用户输入ｎ个数
        if (i < k) {
            max[i] = num[i];    // 将max初始化为前k个输入的数
        }
    }

    // 从第k+1个数开始，将num中的数依次与max中的数比较，如果num中的数小于max中最小的数，则max保持不变
    // 否则，替换掉max中最小的数
    for (int i = k; i < n; i++) {
        // 寻找此时max[]中最小的值 min[1] 及其索引 min[0]
        findMinInMax(max, k);
        // 如果 num[i] > minIndexMinVal[1]，用 num[i] 替换掉目前 max[] 中最小的数 minIndexMinVal[1]
        if (num[i] > minIndexMinVal[1]) {
            max[minIndexMinVal[0]] = num[i];
            continue;
        }
    }
    // 循环结束后，max[]存放着num[]中最大的k个数，其中最小的即为第k大的数
    findMinInMax(max, k);

    cout << minIndexMinVal[1] << endl;  // 输出max中最小的数，即第k大的数

    return 0;
}
