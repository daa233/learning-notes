/**
 * @file: Constructor.cpp
 * @description: 构造函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 13th, 2017
 */

#include <iostream>

using namespace std;

class Complex {
private:
    double real, imag;
public:
    Complex(double r, double i);    // 构造函数也需要声明
    Complex(double r);              // 不同的构造函数是重载的关系
    Complex(Complex c1, Complex c2);
    void set(double r, double i);
};

Complex::Complex(double r, double i) {
    real = r;
    imag = i;
}

Complex::Complex(double r) {
    real = r;
    imag = 0;
}

Complex::Complex(Complex c1, Complex c2) {
    real = c1.real + c2.real;
    imag = c1.imag + c2.imag;
}

int main(int argc, char const *argv[]) {
    // Complex c1;     // error: no matching constructor for initialization of 'Complex'
    // Complex *pc = new Complex;  // error: no matching constructor for initialization of 'Complex'
    Complex c1(2);                      // OK
    Complex c2(2, 4), c3(3, 5);         // OK
    Complex *pc = new Complex(3, 4);    // OK
    return 0;
}
