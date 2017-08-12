/**
 * @filename: CRectangle.cpp
 * @description: 矩形类
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

 #include <iostream>

 using namespace std;

class CRectangle {
public:
    int w, h;
    int Area();
    int Perimeter();
    void Init(int w_, int h_);
};

int CRectangle::Area() {
    return w * h;
}

int CRectangle::Perimeter() {
    return 2 * (w + h);
}

void CRectangle::Init(int w_, int h_) {
    w = w_;
    h = h_;
}

 int main(int argc, char const *argv[]) {
     CRectangle r;
     cout << "Input the width and the height of the rectangle: ";
     cin >> r.w >> r.h;
     cout << "The area of the rectangle is: " << r.Area() << endl;
     cout << "The perimenter of the rectangle is: " << r.Perimeter() << endl;
     return 0;
 }
