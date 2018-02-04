/**
 * 指针与二维数组练习 编程题＃2: 二维数组右上左下遍历
 *
 * @file: Traverse2dArray.cpp
 * @description: 给定一个 row 行 col 列的整数数组 array，要求从 array[0][0] 元素开始，按从左上到右下的对角线顺
                序遍历整个数组。
 * @input: 输入的第一行上有两个整数，依次为 row 和 col。余下有 row 行，每行包含 col 个整数，构成一个二维整数数组。
        （注：输入的 row 和 col 保证 0 < row < 100, 0 < col < 100）
 * @output: 按遍历顺序输出每个整数。每个整数占一行。
 * @sample_input:
    3 4
    1 2 4 7
    3 5 8 10
    6 9 11 12
 * @sample_output:
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    11
    12
 *
 * @author: Du Ang
 * @date: Aug 8th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int m, n;
    cin >> m >> n;
    int a[m][n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0, k = j; k >= 0 && i < m; i++, k--) {
            cout << a[i][k] << endl;
        }
    }
    for (int i = 1; i < m; i++) {
        for (int j = n-1, k = i; k < m && j >= 0; j--, k++) {
            cout << a[k][j] << endl;
        }
    }
    return 0;
}
