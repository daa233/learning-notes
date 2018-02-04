/**
 * C语言中的运算成分 逻辑运算应用练习 综合练习（2）#5：自整除数
 *
 * @file: DivisibleBySelf.cpp
 * @description: 对一个整数n,如果其各个位数的数字相加得到的数m能整除n,则称n为自整除数.例如21,21%(2+1)==0,所以21是自
                整除数.现求出从10到n(n < 100)之间的所有自整除数.
 * @input: 有一行,整数n,(10 <= n < 100)
 * @output: 有多行.按从小到大的顺序输出所有大于等于10,小于等于n的自整除数,每行一个自整除数.
 * 样例输入
    47
 * 样例输出
    10
    12
    18
    20
    21
    24
    27
    30
    36
    40
    42
    45
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    for (int i = 10; i <= n; i++) {
        int dec = i / 10;           // 十位的数字
        int unit = i - 10 * dec;    // 个位的数字
        int sum = dec + unit;       // 个位和十位之和
        if (i % sum == 0) {
            cout << i << endl;      // 如果i能被它的各个数位之和整除，则i是自整除数
        }
    }

    return 0;
}
