/**
 * @file: PrintDecimal.cpp
 * @description: 打印float型和double型
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    float a = 3.1415926535897932384626433832795028841971693993751058209;
    double b = 3.1415926535897932384626433832795028841971693993751058209;
    long double c = 3.1415926535897932384626433832795028841971693993751058209;
    cout << "a = " << a << endl;  // cout默认打印6位精度(6个有效数字)
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    // 设置cout打印精度为50位
    cout << setprecision(50) << "a = " << a << endl;    // float只保证前7个有效位精度
    cout << "b = " << b << endl;    // double 和 long double只保证15个有效位精度
    cout << "c = " << c << endl;

    float x = 0, y = 0;
    x = 123456.789e5;   // 科学计数法表示
    y = x + 20;
    cout << "y = " << setprecision(20) << y << endl;    // 输出12345678848
    // 注意：由于float型精度只有7位，应避免将一个很大的数与一个很小的数相加或相减，否则就会“丢失”小的数。

    return 0;
}
