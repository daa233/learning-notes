/**
 *  2017程序设计夏季学期练习题 编程题＃4 放苹果
 *
 * @file: PlaceApples.cpp
 * @description: 把 M 个同样的苹果放在 N 个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？（用 K 表
                示）5，1，1 和 1，5，1 是同一种分法。
 * @input: 第一行是测试数据的数目 t（0 <= t <= 20）。以下每行均包含二个整数 M 和 N，以空格分开。1 <= M，N <= 10。
 * @output: 对输入的每组数据 M 和 N，用一行输出相应的 K。
 * @sample_input:
    1
    7 3
 * @sample_output:
    8
 *
 * @author: Du Ang
 * @date: Sep. 2nd, 2017
 */

#include <iostream>

using namespace std;

int count(int m, int n) {
    if (m <= 1 || n <= 1) {
        return 1;
    }
    if (m < n) {
        return count(m, m);
    } else {
        return count(m, n - 1) + count(m - n, n);
    }
}

int main(int argc, char const *argv[]) {
    int t;
    cin >> t;
    int m, n;
    while (t--) {
        cin >> m >> n;
        cout << count(m, n) << endl;
    }
    return 0;
}
