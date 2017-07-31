/**
 * @file: PlaceApples.cpp
 * @description: 把 M 个苹果放在 N 个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？
                注意：5,1,1和1,5,1是同一种分法。
 * @input: 输入有两个数，中间用空格隔开。第一个数是苹果的数目，第二个数是盘子的数目。
 * @output: 输出仅一个数，即共有多少种分法。
 * 样例输入：
    7 3
 * 样例输出：
    8
 *
 * @author: Du Ang
 * @date: Apr. 17th, 2017
 */

#include <iostream>

using namespace std;

/*
    1. 先假设有一个函数 count(m, n) 是能够给出正确答案的
    2. 根据假设的函数，分情况讨论
        (1) m < n, 苹果的数目小于盘子的数目，总有盘子是空着的，这些空着的盘子不会影响有多少种分法，可以直接去掉这些空盘子
            count(m, n) = count(m, m);
        (2) m >= n, 苹果的数目大于等于盘子的数目，这时分法可以分为两类
            a. 有盘子空着的分法
                即至少有一个盘子是空的，去掉这个空着的盘子，不会影响分法的种数
                count(m, n) = count(m, n-1);
            b. 没有盘子空着的分法
                每个盘子都至少有一个苹果，那么每个盘子都去掉这个苹果，不会影响最后的分法种数
                count(m, n) = count(m-n, n);
        在 m >= n 时，共有 count(m, n) = count(m, n-1) + count(m-n, n) 种分法
    3. 考虑在最简单的情况下，答案是什么
        苹果个数 m 小于等于1，或者盘子个数 n 小于等于1时，只有一种分法
        count(m, n) = 1;
*/
int count(int m, int n)
{
    if (m <= 1 || n <= 1) return 1; // 我看到的课件写的是n<=0，错误。课件上输入100 100时返回的结果是对的
    if (m < n) {
        return count(m, m);
    } else {
        return count(m, n-1) + count(m-n, n);
    }
}

int main(int argc, char const *argv[]) {
    int m, n;
    cin >> m >> n;
    cout << count(m, n) << endl;
    return 0;
}
