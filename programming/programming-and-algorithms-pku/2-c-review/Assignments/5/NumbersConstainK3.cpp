/**
 * 期末考试 编程题＃1：含 k 个 3 的数
 *
 * @file: NumbersContainK3.cpp
 * @description: 输入二个正整数 m 和 k，其中 1 < m < 100000，1 < k < 5 ，判断 m 能否被 19 整除，且恰好含
                有 k 个 3，如果满足条件，则输出 YES，否则，输出 NO。
 * @input: m 和 k 的值，空格间隔
 * @output: 满足条件时输出 YES，不满足时输出 NO
 * @sample_input:
    43833 3
 * @sample_output:
    YES
 *
 * @author: Du Ang
 * @date: Aug. 10th, 2017
 */

#include <iostream>

using namespace std;

bool containK3(int m, int k)
{
    int count = 0;
    while (m != 0) {
        if (m % 10 == 3) {
            count++;
        }
        m = m / 10;
    }
    if (count == k) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char const *argv[]) {
    int m, k;
    cin >> m >> k;
    if (m % 19 == 0 && containK3(m, k)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
