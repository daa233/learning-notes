/**
 * 综合编程练习（1）编程题 #5：细菌实验分组
 *
 * @file: GroupBacteria.cpp
 * @description: 有一种细菌分为A、B两个亚种，它们的外在特征几乎完全相同，仅仅在繁殖能力上有显著差别，A亚种繁殖能力非常强，B亚种的繁殖能力
                很弱。在一次为时一个 小时的细菌繁殖实验中，实验员由于疏忽把细菌培养皿搞乱了，请你编写一个程序，根据实验结果，把两个亚种的培养
                皿重新分成两组。
 * @input: 输入有多行，第一行为整数n（n≤100），表示有n个培养皿。其余n行，每行有三个整数，分别代表培养皿编号，试验前细菌数量，试验后细菌数量
 * @output: 输出有多行：第一行输出A亚种培养皿的数量，其后每行输出A亚种培养皿的编号，按繁殖率升序排列。然后一行输出B亚种培养皿的数量，其后每行输
            出B亚种培养皿的编号，也按繁殖率升序排列。
 * 样例输入
    5
    1 10 3456
    2 10 5644
    3 10 4566
    4 20 234
    5 20 232
 * 样例输出
    3
    1
    3
    2
    2
    5
    4
 * @hint: 亚种内部细菌繁殖能力差异 远远小于 亚种之间细菌繁殖能力差异。也就是说，亚种间任何两组细菌的繁殖率之差都比亚种内部两组细菌的繁殖率之差大。
 *
 * @author: Du Ang
 * @date: Apr. 16th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n = 0;
    cin >> n;
    int a[n][3] = {0};
    float b[n] = {0};     // 繁殖率
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        b[i] = (float)a[i][2] / a[i][1];
    }
    // 将所有组按繁殖率由小到大排列
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (b[j] > b[j+1]) {
                float temp1 = b[j];
                b[j] = b[j+1];
                b[j+1] = temp1;
                int temp2 = a[j][0];
                a[j][0] = a[j+1][0];
                a[j+1][0] = temp2;
            }
        }
    }
    // 寻找最大差异的相邻两组，它们是A、B亚种的分界线
    int maxDiff = b[1] - b[0];
    int maxDiffIndex = 0;
    for (int i = 1; i < n-1; i++) {
        if (maxDiff < b[i+1] - b[i]) {
            maxDiff = b[i+1] - b[i];
            maxDiffIndex = i;
        }
    }
    cout << n - maxDiffIndex - 1 << endl;   // A亚种数量
    for (int i = maxDiffIndex+1; i < n; i++) {
        cout << a[i][0] << endl;
    }
    cout << maxDiffIndex + 1 << endl;       // B亚种数量
    for (int i = 0; i < maxDiffIndex+1; i++) {
        cout << a[i][0] << endl;
    }
    return 0;
}
