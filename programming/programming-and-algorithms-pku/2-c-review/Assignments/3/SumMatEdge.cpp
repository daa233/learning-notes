/**
 * 指针与二维数组练习 编程题 #1：计算矩阵边缘元素之和
 *
 * @file: SumMatEdge.cpp
 * @description: 输入一个整数矩阵，计算位于矩阵边缘的元素之和。所谓矩阵边缘的元素，就是第一行和最后一行的元素以及第
                一列和最后一列的元素。
 * @input: 第一行为整数k，表示有k组数据。每组数据有多行组成，表示一个矩阵：
        第一行分别为矩阵的行数m和列数n（m < 100，n < 100），两者之间以空格分隔。
        接下来输入的m行数据中，每行包含n个整数，整数之间以空格作为间隔。
 * @output: 输出对应矩阵的边缘元素和，一个一行。
 * @sample_input:
    2
    4 4
    1 1 1 1
    0 0 0 0
    1 0 1 0
    0 0 0 0
    3 3
    3 4 1
    3 7 1
    2 0 1
 * @sample_output:
    5
    15
 *
 * @author: Du Ang
 * @date: Aug. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int k = 0;
    cin >> k;

    while (k) {
        int m = 0;
        int n = 0;
        cin >> m >> n;
        int a[m][n];
        int sum = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
                if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                    sum = sum + a[i][j];
                }
            }
        }
        cout << sum << endl;
        k--;
    }
    return 0;
}
