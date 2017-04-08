/**
 * C程序中的数组 数组应用练习 编程题 #7：中位数
 *
 * @file: Median.cpp
 * @description: 中位数定义：一组数据按从小到大的顺序依次排列，处在中间位置的一个数或最中间两个数据的平均值（如果这组数的个数为奇数，则
                中位数为位于中间位置的那个数；如果这组数的个数为偶数，则中位数是位于中间位置的两个数的平均值）.
                给出一组无序整数，求出中位数，如果求最中间两个数的平均数，向下取整即可（不需要使用浮点数）
 * @input: 该程序包含多组测试数据，每一组测试数据的第一行为N，代表该组测试数据包含的数据个数，1 <= N <= 15000.接着N行为N个数据的
        输入，N=0时结束输入
 * @output: 输出中位数，每一组测试数据输出一行
 * 样例输入
    4
    10
    30
    20
    40
    3
    40
    30
    50
    4
    1
    2
    3
    4
    0
 * 样例输出
    25
    40
    2
 * @hint: 这也是一道经典的算法问题，在企业面试里出现概率很高，是“找到第K大的数”的变种。先排序再找中位数自然是很直接的做法，但排序本身很慢。
        我们只想找到第n/2大的数，对于其他数的顺序我们并不关心。那么怎么在不排序的前提下找到第n/2大的数呢？
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            return 0;
        } else {
            int a[n] = {0};     // 数组的大小为n
            int median = 0;     // 数组的中位数
            for (int i = 0; i < n; i++) {
                cin >> a[i];    // 输入数组
            }

            // 开始寻找数组中前n/2+1个最大的数
            int max[n/2+1]; // 存放前n/2+1个最大的数
            for (int i = 0; i < n/2+1; i++) {
                max[i] = a[i];  // 初始化max[]为a[]的前n/2+1个数
            }
            // 从第n/2+1个数开始，将a中的数依次与max中的数比较，如果num中的数小于max中的每一个数，则max保持不变；
            // 否则，替换掉max中最小的数
            for (int i = n/2+1; i < n; i++) {
                for (int j = 0; j < n/2+1; j++) {
                    // 如果a[i] > max[j]，用a[i]替换掉目前max[]中最小的数
                    if (a[i] > max[j]) {
                        // 寻找此时max[]中最小的值tempMin及其索引tempMinIndex
                        int tempMin = max[0];   // 用于存储此时max[]中的最小值
                        int tempMinIndex = 0;  // 用于存储此时max[]中最小值的索引
                        // 找到max[]此时最小值的索引
                        for (int l = 1; l < n/2+1; l++) {
                            // 如果tempMin大于max[i]，更新tempMin和tempMinIndex为max[i]和i
                            if (tempMin > max[l]) {
                                tempMin = max[l];
                                tempMinIndex = l;
                            }
                        }
                        max[tempMinIndex] = a[i];     // 用num[i]更新max[]中的最小值
                        break;  // 退出本次循环，比较num[]中的下一个数
                    }
                }
            }
            // 循环结束后，max[]存放着a[]中最大的k个数，其中最小的即为第n/2+1大的数
            int min = max[0];   // 用于存储此时max[]中的最小值
            int minIndex = 0;   // 用于存储此时max[]中最小值的索引
            // 找到max[]此时最小值的索引
            for (int i = 1; i < n/2+1; i++) {
                // 如果tempMin小于max[i]，更新tempMin和tempMinIndex为max[i]和i
                if (min > max[i]) {
                    min = max[i];
                    minIndex = i;
                }
            }
            if (n % 2 != 0) {
                // n为奇数，找到第(n/2+1)大的数即为其中位数
                median = min;
            } else {
                // n为偶数，还要找到第n/2大的数，即max[]中第二小的数并求它们的平均值
                int secondMin = max[0];
                int secondMinIndex = 0;
                for (int i = 1; i < n/2+1; i++) {
                    if (i == minIndex) continue;    // 忽略掉max[]中最小的数
                    if (secondMin > max[i]) {
                        secondMin = max[i];
                        secondMinIndex = i;
                    }
                }
                median = (min + secondMin) / 2;
            }
            cout << median << endl; // 打印最后的结果
        }
    }

    return 0;
}
