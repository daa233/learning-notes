/**
 * @file: PrintHex.cpp
 * @description: 打印十六进制数，数的进制之间的转换
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int a = -123;
    int h = 0xFFFFFF85;     // h以0x开头，为十六进制数，F不区分大小写
    unsigned int uh = 0xFFFFFF85;   // 无符号十六进制数uh，值和h相同，转换成二进制后值不同
    int o = 037777777605;   // o以0开头，为八进制数

    // 通过控制打印输出，完成数制间的转换
    cout << hex << a << endl;   // hex为十六进制打印控制符
    cout << oct << a << endl;   // oct为八进制打印控制符
    cout << dec << a << endl;   // dec为十进制打印控制符
    cout << h << endl;
    cout << uh << endl;
    cout << o << endl;
    // 注意：同一程序内，设定打印控制符后，之后所有的打印默认设定的打印控制符。

    // int unInitNum;   // 测试不赋初值的情况
    // cout << unInitNum << endl;

    return 0;
}
