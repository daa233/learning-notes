/**
 *  文件操作和模板 编程题＃2
 *
 * @file: Week7Ex2.cpp
 * @description: 程序填空
            利用流操纵算子实现： 输入一个实数，先以非科学计数法输出，小数点后面保留 5 位有效数字；再以科学计数法输出，
            小数点后面保留 7 位有效数字。
            注意：在不同系统、编译器上的输出格式略有不同，但保证在程序中采用默认格式设置一定能在 OJ 平台上得到正确结
            果。
 * @input: 以非科学计数法表示的一个正实数，保证可以用 double 类型存储。
 * @output:
    第一行：以非科学计数法输出该实数，小数点后面保留 5 位有效数字；
    第二行：以科学计数法输出该实数，小数点后面保留 7 位有效数字。
 * @sample_input:
    12.34
 * @sample_output:
    12.34000
    1.2340000e+01
 *
 * @author: Du Ang
 * @date: Aug. 26th, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[]) {
    double n;
    cin >> n;
    cout << fixed << setprecision(5) << n << endl;
    cout << setprecision(7) << scientific << n << endl;
    return 0;
}
