/**
 *  文件操作和模板 编程题＃3
 *
 * @file: Week7Ex3.cpp
 * @description: 程序填空
            利用流操纵算子实现：输入一个整数，先将该整数以十六进制输出，然后再将该整数以 10 个字符的宽度输出，宽度
            不足时在左边补 0。
            注意：在不同系统、编译器上的输出格式略有不同，但保证在程序中采用默认格式设置一定能在 OJ 平台上得到正确结
            果。
 * @input: 一个正整数，保证可以用 int 类型存储。
 * @output:
    第一行：以十六进制输出该整数；
    第二行：以10个字符的宽度输出该整数。
 * @sample_input:
    23
 * @sample_output:
    17
    0000000023
 *
 * @author: Du Ang
 * @date: Aug. 26th, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    cout << setbase(16) << n << endl;
    cout << setbase(10) << setw(10) << setfill('0') << n << endl;
    return 0;
}
