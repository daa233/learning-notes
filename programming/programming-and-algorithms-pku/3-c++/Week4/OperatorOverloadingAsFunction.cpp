/**
 * @file: OperatorOverloadingAsNormalFunction.cpp
 * @description: 运算符重载为普通函数和成员函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 18th, 2017
 */

#include <iostream>

class ComplexN {
public:
    ComplexN(double r = 0.0, double i = 0.0) {
        real = r;
        imaginary = i;
    }
    double real;
    double imaginary;
};

ComplexN operator+(const ComplexN &a, const ComplexN &b) {
    return ComplexN(a.real + b.real, a.imaginary + b.imaginary);
}

class ComplexM {
public:
    ComplexM(double r = 0.0, double m = 0.0) : real(r), imaginary(m) {}
    ComplexM operator+(const ComplexM &);
    ComplexM operator-(const ComplexM &);
private:
    double real;
    double imaginary;
};

ComplexM ComplexM::operator+(const ComplexM &operand) {
    return ComplexM(real + operand.real, imaginary + operand.imaginary);
}

ComplexM ComplexM::operator-(const ComplexM &operand) {
    return ComplexM(real - operand.real, imaginary - operand.imaginary);
}

int main(int argc, char const *argv[]) {
    ComplexN a(1, 2), b(2, 3), c;
    c = a + b;
    std::cout << c.real << " + " << c.imaginary << "i" << std::endl;

    ComplexM x, y(4.3, 8.2), z(3.3, 1.1);
    x = y + z;  // same as x = y.operator+(z);
    x = y - z;  // same as x = y.operator-(z);
    return 0;
}
