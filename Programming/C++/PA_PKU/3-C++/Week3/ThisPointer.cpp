/**
 * @file: ThisPointer.cpp
 * @description: this 指针
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 15th, 2017
 */

#include <iostream>

class Complex {
public:
    double real, imag;
    void Print() {
        std::cout << real << "," << imag << std::endl;
    }
    Complex(double r, double i) : real(r), imag(i) {}
    Complex AddOne() {
        this->real++;
        this->Print();
        return *this;
    }
};

class A {
private:
    int i;
public:
    void Hello() {
        std::cout << "Hello world!" << std::endl;
    }
};

class B {
private:
    int i;
public:
    void Hello() {
        std::cout << i << " Hello world!" << std::endl;
    }
};

int main(int argc, char const *argv[]) {
    Complex c1(1, 1), c2(0, 0);
    c2 = c1.AddOne();   // 2,1

    A *p1 = NULL;
    p1->Hello();
    B *p2 = NULL;
    p2->Hello();
    return 0;
}
