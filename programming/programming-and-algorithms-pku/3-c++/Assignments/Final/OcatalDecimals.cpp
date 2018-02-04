/**
 *  2017程序设计夏季学期练习题 编程题＃6 八进制小数
 *
 * @file: OcatalDecimals.cpp
 * @description: 八进制有限小数均可以用十进制有限小数精确地表示。比如，八进制里面的 0.75 等于十进制里面的
                0.963125 (7/8 + 5/64)。所有小数点后位数为n的八进制小数都可以表示成小数点后位数不多于 3n 的十进
                制小数。
                你的任务是写一个程序，把 (0,1) 之间的八进制小数转化成十进制小数。
 * @input: 一行，包含一个八进制小数。每个小数的形式是 0.d1d2d3 ... dk，这里 di 是八进制数 0...7，dk 不等于 0，
        而且已知 0 < k < 15。
 * @output: 输入如下形式的一行
        0.d1d2d3...dk [8] = 0.D1D2D3...Dm [10]
        这里左边是输入的八进制小数，右边是相等的十进制小数。输出的小数末尾不能有 0，也就是说 Dm 不等于 0。注意空格位
        置。
 * @sample_input:
    0.75
 * @sample_output:
    0.75 [8] = 0.953125 [10]
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>
#include <iomanip>  // for setprecision()
#include <math.h>   // for pow()

using namespace std;

int main(int argc, char const *argv[]) {
    double decimal = 0; // the decimal result
    char dummy;         // to eat the '0.' of the octal decimal
    string octalDecimalPart;
    cin >> dummy >> dummy;
    cin >> octalDecimalPart;
    for (int i = 0; i < octalDecimalPart.size(); i++) {
        decimal = decimal + (octalDecimalPart[i] - '0') * pow(8, -(i+1));
    }
    cout << "0." << octalDecimalPart << " [8] = "
        << setprecision(42) << decimal << " [10]"<< endl;
    return 0;
}
