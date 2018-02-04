/**
 * 综合编程练习（2） 编程题＃3：寻找山顶
 *
 * @file: FindPeak.cpp
 * @description: 在一个 m×n 的山地上，已知每个地块的平均高程，请求出所有山顶所在的地块（所谓山顶，就是其地块平均高
                程不比其上下左右相邻的四个地块每个地块的平均高程小的地方)。
 * @input: 第一行是两个整数，表示山地的长 m（5 ≤ m ≤ 20）和宽 n（5 ≤ n ≤ 20）。其后 m 行为一个 m×n 的整数矩阵，
        表示每个地块的平均高程。每行的整数间用一个空格分隔。
 * @output: 输出所有上顶所在地块的位置。每行一个。按先 m 值从小到大，再 n 值从小到大的顺序输出。
 * @sample_input:
    10 5
    0 76 81 34 66
    1 13 58 4 40
    5 24 17 6 65
    13 13 76 3 20
    8 36 12 60 37
    42 53 87 10 65
    42 25 47 41 33
    71 69 94 24 12
    92 11 71 3 82
    91 90 20 95 44
 * @sample_output:
    0 2
    0 4
    2 1
    2 4
    3 0
    3 2
    4 3
    5 2
    5 4
    7 2
    8 0
    8 4
    9 3
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
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

    // In total 9 cases
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                if (j == 0) {
                    if (a[i][j] >= a[i+1][j] && a[i][j] >= a[i][j+1])
                        cout << i << " " << j << endl;
                } else if (j == n - 1) {
                    if (a[i][j] >= a[i][j-1] && a[i][j] >= a[i+1][j])
                        cout << i << " " << j << endl;
                } else {
                    if (a[i][j] >= a[i+1][j] && a[i][j] >= a[i][j+1] && a[i][j] >= a[i][j-1])
                        cout << i << " " << j << endl;
                }
            } else if (i == m - 1) {
                if (j == 0) {
                    if (a[i][j] >= a[i-1][j] && a[i][j] >= a[i][j+1])
                        cout << i << " " << j << endl;
                } else if (j == n - 1) {
                    if (a[i][j] >= a[i][j-1] && a[i][j] >= a[i-1][j])
                        cout << i << " " << j << endl;
                } else {
                    if (a[i][j] >= a[i-1][j] && a[i][j] >= a[i][j+1] && a[i][j] >= a[i][j-1])
                        cout << i << " " << j << endl;
                }
            } else {
                if (j == 0) {
                    if (a[i][j] >= a[i-1][j] && a[i][j] >= a[i+1][j] && a[i][j] >= a[i][j+1])
                        cout << i << " " << j << endl;
                } else if (j == n - 1) {
                    if (a[i][j] >= a[i-1][j] && a[i][j] >= a[i+1][j] && a[i][j] >= a[i][j-1])
                        cout << i << " " << j << endl;
                } else {
                    if (a[i][j] >= a[i-1][j] && a[i][j] >= a[i+1][j] && a[i][j] >= a[i][j-1] \
                        && a[i][j] >= a[i][j+1])
                        cout << i << " " << j << endl;
                }
            }
        }
    }
    return 0;
}
