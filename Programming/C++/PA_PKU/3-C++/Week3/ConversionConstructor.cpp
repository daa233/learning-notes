/**
 * @file: ConversionConstructor.cpp
 * @description: 转换构造函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 13th, 2017
 */

#include <iostream>

using namespace std;

class Complex {
public:
    double real, imag;
    Complex(int i) {    // 类型转换构造函数
        cout << "Int constructor of Complex is called." << endl;
        real = i;
        imag = 0;
    }
    Complex(double r, double i) {
        cout << "Constructor of Complex is called." << endl;
        real = r;
        imag = i;
    }
};

int main(int argc, char const *argv[]) {
    Complex c1(7, 8);
    // Constructor of Complex is called.
    Complex c2 = 12;    // 注意这里的 = 是初始化，不是赋值
    // Int constructor of Complex is called.
    c1 = 9; // OK. 9 被自动转换成一个临时的 Complex 对象，然后赋值给 c1
    // Int constructor of Complex is called.
    return 0;
}
