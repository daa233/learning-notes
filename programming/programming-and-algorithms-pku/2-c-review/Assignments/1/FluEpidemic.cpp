/**
 * 综合编程练习（1）编程题 #6：流感传染
 *
 * @file: FluEpidemic.cpp
 * @description: 有一批易感人群住在网格状的宿舍区内，宿舍区为n*n的矩阵，每个格点为一个房间，房间里可能住人，也可能空着。在第一天，有些房间
                里的人得了流感，以后每天，得流感的人会使其邻居传染上流感，（已经得病的不变），空房间不会传染。请输出第m天得流感的人数。
 * @input: 第一行一个数字n，n不超过100，表示有n*n的宿舍房间。接下来的n行，每行n个字符，’.’表示第一天该房间住着健康的人，’#’表示该房
            间空着，’@’表示第一天该房间住着得流感的人。接下来的一行是一个整数m，m不超过100
 * @output: 输出第m天，得流感的人数
 * 样例输入
    5
    ....#
    .#.@.
    .#@..
    #....
    .....
    4
 * 样例输出
    16
 *
 * @author: Du Ang
 * @date: Apr. 16th, 2017
 */

#include <iostream>

using namespace std;

#define N 100

int countPatients(char a[][N], int n);  // 统计病人数
void toNextDay(char a[][N], char b[][N], int n);    // 当前是a状态，下一天是b状态
void infect(char a[][N], char b[][N], int n, int i, int j); // a[i][j]感染周围病人

int main(int argc, char *argv[])
{
    int n = 0;
    cin >> n;
    char a[N][N] = {'.'};   // a、b交替表示不同天的病房状态
    char b[N][N] = {'.'};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    int m = 0;
    cin >> m;       // 经过m天

    if (m > 1) {
        for (int i = 2; i <= m; i++) {
            if (i % 2 == 0) {
                toNextDay(a, b, n);
            } else {
                toNextDay(b, a, n);
            }
        }
    } else {
        return -1;
    }
    if (m % 2 == 0) {
        cout << countPatients(b, n) << endl;
    } else {
        cout << countPatients(a, n) << endl;
    }


    return 0;
}

// 统计当前的病人总数
int countPatients(char a[][N], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            switch (a[i][j]) {
                case '@':
                    count++;
                    break;
                default:
                    break;
            }
        }
    }
    return count;
}

// 由a --> b。a表示当天病房情况，b表示下一天病房情况
void toNextDay(char a[][N], char b[][N], int n)
{
    // 将当前病房状态由a复制到b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '.' || a[i][j] == '#') {
                continue;
            } else if (a[i][j] == '@') {
                infect(a, b, n, i, j);
            }
        }
    }
}

// a[i][j]病人开始感染周围的人，结果记录于b矩阵中
void infect(char a[][N], char b[][N], int n, int i, int j)
{
    if (i != n && a[i+1][j] != '#' && a[i+1][j] != '@') {
        b[i+1][j] = '@';
    }
    if (i != 0 && a[i-1][j] != '#' && a[i-1][j] != '@') {
        b[i-1][j] = '@';
    }
    if (j != n && a[i][j+1] != '#' && a[i][j+1] != '@') {
        b[i][j+1] = '@';
    }
    if (j != 0 && a[i][j-1] != '#' && a[i][j-1] != '@') {
        b[i][j-1] = '@';
    }
}
