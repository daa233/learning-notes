/**
 * C语言中的数据成分 数据成分应用练习 抄写题 #2：分数求和（改进版）
 *
 * @file: SumFractionImprove.cpp
 * @description: 输入n个分数并对他们求和，用约分之后的最简形式表示。
                比如：q/p = x1/y1 + x2/y2 +....+ xn/yn，q/p要求是归约之后的形式。
                如：5/6已经是最简形式，3/6需要规约为1/2, 3/1需要规约成3，10/3就是最简形式。
                PS:分子和分母都没有为0的情况，也没有出现负数的情况
                我们计算过程中结果分母是不断乘以新输入的分母，最后约分的。这样可能导致这个过程中分母过大溢出。
                这道题的数据比较简单，并没有出现那种情况。但大家可以思考一下，如果出现了那种情况怎么办呢？（不要用大整数啊）
                我给大家一组测试数据，看看你修改过的程序能不能通过这组数据吧：
                    样例输入：
                    2
                    1/100000000
                    1/100000000
                    样例输出：
                    1/50000000
 * @input: 第一行的输入n,代表一共有几个分数需要求和，接下来的n行是分数
 * @output: 输出只有一行，即归约后的结果
 * 样例输入
    2
    1/2
    1/3
 * 样例输出
    5/6
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int findGCD(int a, int b);  // 自定义函数，求a和b的最大公约数
int findLCM(int a, int b);  // 自定义函数，求a和b的最小公倍数

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    int sumn = 0, sumd = 1; // 储存结果，sumn/sumd
    char slash; // 专门用来吃掉/的
    if (n == 1) {
        // 只有一个分数的情况
        cin >> sumn >> slash >> sumd;   // 输入分数
        // 求最大公约数gcd
        int gcd = findGCD(sumn, sumd);
        sumd /= gcd;
        sumn /= gcd;
    } else {
        // 有多个分数的情况
        int num, deno;    // 存放后续分数的分子num和分母deno
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                cin >> sumn >> slash >> sumd;  // 输入第一个分数sumn/sumd
            } else {
                cin >> num >> slash >> deno;  // 后续的分数输入num/deno
                // 求两个分母的最小公倍数lcm
                int lcm = findLCM(sumd, deno);
                sumn = lcm / deno * num + lcm / sumd * sumn;    // 相加后的分子
                sumd = lcm;     // 相加后的分母即为最小公倍数
                // cout << "未化简：sumn/sumd = " << sumn << "/" << sumd << endl;
                // 化简相加后的分数
                int gcd = findGCD(sumn, sumd);      // 求分子分母最大公约数gcd
                sumd /= gcd;
                sumn /= gcd;
                // cout << "化简后：sumn/sumd = " << sumn << "/" << sumd << endl;
            }
        }
    }
    // 最后结果
    if (sumd > 1)
        cout << sumn << '/' << sumd << endl;
    else
        cout << sumn << endl;
    return 0;
}

// 实现函数findGCD()，求两个数的最大公约数
int findGCD(int a, int b)
{
    // 求最大公约数，这里用的是欧几里得法
    int c;
    while (a != 0) {
        c = a; a = b%a; b = c;
    }
    return b;
}

// 实现函数findLCM()，求两个数的最小公倍数
int findLCM(int a, int b)
{
    // a、b的最小公倍数等于a、b的乘积除以a、b的最大公约数。注意a、b很大，这里要避免a、b相乘。
    return a / findGCD(a, b) * b;
}
