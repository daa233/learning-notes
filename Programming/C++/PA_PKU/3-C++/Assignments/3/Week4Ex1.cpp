/**
 *  运算符重载 编程题＃1
 *
 * @file: Week4Ex1.cpp
 * @description: 程序填空
                下面程序的输出是：
                    3+4i
                    5+6i
                请补足 Complex 类的成员函数。不能加成员变量。
 * @sample_input:
    none
 * @sample_output:
    3+4i
    5+6i
 *
 * @author: Du Ang
 * @date: Aug. 21st, 2017
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
    // 在此处补充你的代码
    Complex &operator=(const char *str) {       // assignment operator overloading
        const char *pos = strchr(str, '+');     // get the position of '+'
        int strLen = strlen(str);               // get the length of str
        int posLen = strlen(pos);               // get the length of the substring "+...i"
        char *real = new char[strLen];          // real part substring
        char *imag = new char[strLen];          // imaginary part substring
        strncpy(real, str, strLen - posLen);    // get real part from str
        real[strLen-posLen] = '\0';
        strncpy(imag, pos+1, posLen - 2);       // get imaginary part from str
        imag[posLen-2] = '\0';

        r = atof(real);                         // convert char * to float
        i = atof(imag);

        delete[] real;
        delete[] imag;
        return *this;
    }
};

int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
