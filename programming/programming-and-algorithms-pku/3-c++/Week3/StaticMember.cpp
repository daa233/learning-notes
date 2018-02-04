/**
 * @file: StaticMember.cpp
 * @description: 静态成员变量和静态成员函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 14th, 2017
 */

#include <iostream>

class CRectangle {
private:
    int w, h;
    static int nTotalArea;      // declare static member variable nTotalArea
    static int nTotalNumber;    // declare static member variable nTotalNumber
public:
    CRectangle(int w_, int h_);
    CRectangle(const CRectangle &r);
    ~CRectangle();
    static void PrintTotal();   // declare static member function PrintTotal()
};

/*
 * The declaration of a static data member in the member list of a class is not a definition.
 * You must define the static member outside of the class declaration, in namespace scope.
 * When define the static member variables in the namespace scope, we can also chooose to
 * initialize it even it is a private member variable. If no initializer is provided, C++
 * initializes the value to 0.
 */
int CRectangle::nTotalNumber = 0;
int CRectangle::nTotalArea = 0;

CRectangle::CRectangle(int w_, int h_) {
    w = w_;
    h = h_;
    nTotalNumber++;
    nTotalArea += w * h;
}

CRectangle::CRectangle(const CRectangle &r) {
    w = r.w;
    h = r.h;
    nTotalNumber++;
    nTotalArea += w * h;
}

CRectangle::~CRectangle() {
    nTotalNumber--;
    nTotalArea -= w * h;
}

void CRectangle::PrintTotal() {
    std::cout << nTotalNumber << ", " << nTotalArea << std::endl;
}

int main(int argc, char const *argv[]) {
    CRectangle r1(3, 3), r2(2, 2);

    // error: 'nTotalNumber' is a private member of 'CRectangle'
    // std::cout << CRectangle::nTotalNumber << std::endl;

    CRectangle::PrintTotal();
    r1.PrintTotal();
    return 0;
}
