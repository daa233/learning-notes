/**
 * @file: OperatorOverloadingAsFriend.cpp
 * @description: 运算符重载为友元
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 20th, 2017
 */

#include <iostream>

class Complex {
private:
    double real, imag;
public:
    Complex(double r, double i) : real(r), imag(i) {}
    Complex operator+(double r);
    friend Complex operator+(double r, const Complex &c);
    void print() {
        std::cout << real << " + " << imag << " i" << std::endl;
    }
};

Complex Complex::operator+(double r) {
    return Complex(real + r, imag);
}

Complex operator+(double r, const Complex &c) {
    return Complex(c.real + r, c.imag);
}

int main(int argc, char const *argv[]) {
    Complex c(1, 3);
    c.print();
    c = c + 5;
    c.print();
    c = 5 + c;
    c.print();
    return 0;
}
