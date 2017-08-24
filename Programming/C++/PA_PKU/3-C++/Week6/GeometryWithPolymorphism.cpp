/**
 * @file: GeometryWithPolymorphism.cpp
 * @description: 更多多态程序实例——几何形体处理程序
                几何形体处理程序：输入若干个几何形体的参数，要求按面积排序输出。输出时要指明形状。
 * @input: 第一行是几何形体数目 n （不超过 100）。下面有 n 行，每行以一个字母 c 开头。
        若 c 是 ‘R’，则代表一个矩形，本行后面跟着两个整数，分别是矩形的宽和高；
        若 c 是 ‘C’，则代表一个圆，本行后面跟着一个整数代表其半径
        若 c 是 ‘T’，则代表一个三角形，本行后面跟着三个整数，代表三条边的长度
 * @output: 按面积从小到大依次输出每个几何形体的种类和面积。每行一个几何形体，输出格式为：
        形体名称:面积
 * @sample_input:
    3
    R 3 5
    C 9
    T 3 4 5
 * @sample_output:
    Triangle:6
    Rectangle:15
    Circle:254.34
 *
 * @author: Du Ang
 * @date: Aug. 23rd, 2017
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

class CShape {
public:
    virtual double area() = 0;      // pure virtual function
    virtual void printInfo() = 0;   // pure virtual function
};

class CRectangle : public CShape {
public:
    int w, h;
    virtual double area();
    virtual void printInfo();
};

class CCircle : public CShape {
public:
    int r;
    virtual double area();
    virtual void printInfo();
};

class CTriangle : public CShape {
public:
    int a, b, c;
    virtual double area();
    virtual void printInfo();
};

double CRectangle::area() {
    return w * h;
}

void CRectangle::printInfo() {
    cout << "Rectangle:" << area() << endl;
}

double CCircle::area() {
    return 3.14 * r * r;
}

void CCircle::printInfo() {
    cout << "Circle:" << area() << endl;
}

double CTriangle::area() {
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));   // Heron's formula
}

void CTriangle::printInfo() {
    cout << "Triangle:" << area() << endl;
}

CShape *pShapes[100];   // base class pointers array

int myCompare(const void *s1, const void *s2);

int main(int argc, char const *argv[]) {
    int i;
    int n;  // the number of shapes
    CRectangle *pr;
    CCircle *pc;
    CTriangle *pt;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        switch (c) {
            case 'R':   // Rectangle
                pr = new CRectangle();
                cin >> pr->w >> pr->h;  // width height
                pShapes[i] = pr;
                break;
            case 'C':   // Circle
                pc = new CCircle();
                cin >> pc->r;           // radius
                pShapes[i] = pc;
                break;
            case 'T':   // Triangle
                pt = new CTriangle();
                cin >> pt->a >> pt->b >> pt->c; // a b c (the length of the triangle's three edges)
                pShapes[i] = pt;
                break;
            default:
                break;
        }
    }
    qsort(pShapes, n, sizeof(CShape*), myCompare);
    for (i = 0; i < n; i++)
        pShapes[i]->printInfo();    // polymorphism

    return 0;
}

int myCompare(const void *s1, const void *s2) {
    double a1, a2;
    CShape **p1;        // s1, s2 is void * type, p1, p2 points to ponter type
    CShape **p2;
    p1 = (CShape **)s1; // s1 points to the element of pShapes array, the element type is CShape *
    p2 = (CShape **)s2;
    a1 = (*p1)->area(); // polymorphism. *p1's type is CShape *, *p1 is a pointer of base class
    a2 = (*p2)->area();

    if (a1 < a2)
        return -1;
    else if (a2 < a1)
        return 1;
    else
        return 0;
}
