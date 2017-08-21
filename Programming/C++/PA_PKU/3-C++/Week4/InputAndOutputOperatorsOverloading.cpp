/**
 * 流插入运算符和流提取运算符重载
 *
 * @file: InputAndOutputOperatorsOverloading.cpp
 * @description: 重载流插入运算符 >> 和流提取运算符 <<
                1. 使 cout << s << "hello"; 输出 "5hello"
                2. 假定 c 是 Complex 复数类的对象，现在希望写 cout << c; 就能以 “a+bi” 的形式输出；
                写 cin >> a+bi; 就能从键盘接受“a+bi”形式的输入，并且使得 c.real = a, c.imag = b;
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 21st, 2017
 */

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class CStudent {
public:
    int nAge;
};

ostream &operator<<(ostream &o, const CStudent &s) {
    o << s.nAge;
    return o;
}

class Complex {
private:
    double real;
    double imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {};
    friend ostream &operator<<(ostream &os, const Complex &c);
    friend istream &operator>>(istream &is, Complex &c);
};

ostream &operator<<(ostream &os, const Complex &c) {
    os << c.real << "+" << c.imag << "i";
    return os;
}

istream &operator>>(istream &is, Complex &c) {
    string s;
    is >> s;
    int pos = s.find("+", 0);
    string sTmp = s.substr(0, pos); // get real part
    c.real = atof(sTmp.c_str());    // convert const char * to float
    sTmp = s.substr(pos+1, s.length()-pos-2);   // get imaginary part
    c.imag = atof(sTmp.c_str());
    return is;
}

int main(int argc, char const *argv[]) {
    CStudent s;
    s.nAge = 5;
    cout << s << "hello" << endl;   // 5hello

    Complex c;
    int n;
    cin >> c >> n;
    cout << c << "," << n << endl;

    return 0;
}
