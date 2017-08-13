/**
 * @file: MemeberFunctionOverloading.cpp
 * @description: 成员函数的重载及参数缺省
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 13th, 2017
 */

#include <iostream>

using namespace std;

class Location {
private:
    int x;
    int y;
public:
     void init(int x = 0, int y = 0);   // 可以在声明或实现时定义默认参数，但不能二者同时定义
     void value_x(int val) {x = val;}
     int value_x() {return x;}          // 重载函数返回类型可以不一样
};

void Location::init(int X, int Y) {
    x = X;
    y = Y;
}

int main(int argc, char const *argv[]) {
    Location A;
    A.init(5);
    A.value_x(5);
    cout << A.value_x() << endl;
    A.value_x();
    cout << A.value_x() << endl;
    return 0;
}
