/**
 * 期末考试 编程题＃4：寻找平面上的极大点
 *
 * @file: FindMaxPoint.cpp
 * @description: 在一个平面上，如果有两个点 (x, y), (a, b), 如果说 (x, y) 支配了 (a, b)，这是指 x >= a,
                y >= b; 用图形来看就是 (a, b) 坐落在以 (x, y) 为右上角的一个无限的区域内。给定 n 个点的集合，
                一定存在若干个点，它们不会被集合中的任何一点所支配，这些点叫做极大值点。编程找出所有的极大点，按照
                x 坐标由小到大，输出极大点的坐标。
                本题规定：n 不超过 100，并且不考虑点的坐标为负数的情况。
 * @input: 输入包括两行，第一行是正整数 n，表示是点数，第二行包含 n 个点的坐标，坐标值都是整数，坐标范围从 0 到
        100，输入数据中不存在坐标相同的点。
 * @output: 按 x 轴坐标最小到大的顺序输出所有极大点。输出格式为: (x1,y1),(x2,y2),...(xk,yk)
        注意：输出的每个点之间有","分隔,最后一个点之后没有",",少输出和多输出都会被判错
 * @sample_input:
    5
    1 2 2 2 3 1 2 3 1 4
 * @sample_output:
    (1,4),(2,3),(3,1)
 *
 * @author: Du Ang
 * @date: Aug. 10th, 2017
 */

#include <iostream>

using namespace std;

struct point {
    int x;
    int y;
};

void sortPointsByX(point p[], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i -1; j++) {
            if (p[j].x > p[j+1].x) {
                point temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

bool isMaxPoint(point p[], int m, int n)
{
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (i != m) {
            if (p[i].x >= p[m].x && p[i].y >= p[m].y) {
                flag = false;
            }
        }
    }
    return flag;
}

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    point p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    sortPointsByX(p, n);

    bool isFirstMaxPoint = true;
    for (int i = 0; i < n; i++) {
        if (isMaxPoint(p, i, n)) {
            if (isFirstMaxPoint) {
                cout << "(" << p[i].x << "," << p[i].y << ")";
            } else {
                cout << ",(" << p[i].x << "," << p[i].y << ")";
            }
            isFirstMaxPoint = false;
        }
    }
    cout << endl;
    return 0;
}
