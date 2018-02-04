/**
 * C程序中的数组 数组应用练习 编程题 #8：校门外的树（改进版）
 *
 * @file: AvenueTreesImprove.cpp
 * @description: 某校大门外长度为L的马路上有一排树，每两棵相邻的树之间的间隔都是1米。我们可以把马路看成一个数轴，马路的一端在数轴0的
                位置，另一端在L的位置；数轴上的每个整数点，即0，1，2，……，L，都种有一棵树。马路上有一些区域要用来建地铁，这些区域用
                它们在数轴上的起始点和终止点表示。已知任一区域的起始点和终止点的坐标都是整数，区域之间可能有重合的部分。现在要把这些
                区域中的树（包括区域端点处的两棵树）移走。你的任务是计算将这些树都移走后，马路上还有多少棵树。
 * @input: 输入的第一行有两个整数L（1 <= L <= 10000）和 M（1 <= M <= 100），L代表马路的长度，M代表区域的数目，L和
        M之间用一个空格隔开。接下来的M行每行包含两个不同的整数，用一个空格隔开，表示一个区域的起始点和终止点的坐标。
 * @output: 输出包括一行，这一行只包含一个整数，表示马路上剩余的树的数目。
 * 样例输入
    第一组
    500 3
    150 300
    100 200
    470 471
    第二组
    500 3
    100 200
    150 160
    180 190
 * 样例输出
    第一组
    298
    第二组
    400
 * @hint: 由于数据范围不大（L<=10000），我们可以使用一个10001长度的数组来记录每一个坐标上有没有树。但想象一下如果数据范围很大，比如
        下面这个情况，你怎么办呢？
        输入
        5000000 3
        1500000 3000000
        1000000 2000000
        4700000 4700001
        输出
        2999998
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int l = 0, m = 0;   // 树的总数，区域的数目
    cin >> l >> m;      // 输入l和m
    int regions[m][2] = {0};  // 区域的坐标
    bool combinedFlags[m] = {false};  // 用于标识一个区域是否可以被合并
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> regions[i][j];   // 输入各区域坐标
            // 对坐标进行越界处理
            if (regions[i][j] > l) {
                regions[i][j] = l;
            } else if (regions[i][j] < 0) {
                regions[i][j] = 0;
            }
        }
    }

    // 为了方便计算剩余的数目，对可能重合的区域进行合并。区域i和区域j共有6种可能的位置关系,重合关系有4种
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < m; j++) {
            // 目前两个区域都没被其他区域合并，而且不是同一个区域
            if (!combinedFlags[i] && !combinedFlags[j] && i != j) {
                if (regions[j][0] >= regions[i][0]
                    && regions[j][0] <= regions[i][1]
                    && regions[j][1] > regions[i][1]) {
                    combinedFlags[j] = true;        // 区域j可以被合并入区域i
                    regions[i][1] = regions[j][1];  // 更新区域i右边界
                    i = 0; j = 1; continue;         // 重新检测重合区域
                } else if (regions[j][0] >= regions[i][0]
                            && regions[j][1] <= regions[i][1]) {
                    combinedFlags[j] = true;        // 区域j可以被合并入区域i
                    i = 0; j = 1; continue;         // 重新检测重合区域
                } else if (regions[j][0] < regions[i][0]
                            && regions[j][1] >= regions[i][0]
                            && regions[j][1] <= regions[i][1]) {
                    combinedFlags[i] = true;        // 区域i可以被合并入区域j
                    regions[j][1] = regions[i][1];  // 更新区域j右边界
                    i = 0; j = 1; continue;         // 重新检测重合区域
                } else if (regions[j][0] < regions[i][0]
                            && regions[j][1] > regions[i][1]) {
                    combinedFlags[i] = true;        // 区域i可以被合并入区域j
                    i = 0; j = 1; continue;         // 重新检测重合区域
                }
            }
        }
    }

    // 到这里已经不存在重合区域了，计算剩余树木数
    int remain = l + 1;     // 剩余树木数
    for (int i = 0; i < m; i++) {
        if (combinedFlags[i]) continue;
        remain = remain - (regions[i][1] - regions[i][0] + 1);
    }
    cout << remain << endl;

    return 0;
}
