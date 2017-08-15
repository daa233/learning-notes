/**
 * @file: Friend.cpp
 * @description: 友元
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 14th, 2017
 */

#include <iostream>

using namespace std;

// 提前声明 CCar 类，以便后面 CDriver 类使用
class CCar; // 前置声明（forward declaration）

class CDriver {
public:
    void ModifyCar(CCar *pCar); // 改装汽车
};

class CCar {
private:
    int price;
    friend int MoseExpensiveCar(CCar cars[], int total);    // 将普通函数声明为友元
    friend void CDriver::ModifyCar(CCar *pCar);             // 将其他类的成员函数声明为友元
};

void CDriver::ModifyCar(CCar *pCar) {
    pCar->price += 1000;    // 汽车改装后价值增加
}

int MostExpensiveCar(CCar cars[], int total) {
    int tmpMax = -1;
    for (int i = 0; i < total; ++i) {
        if (cars[i].price > tmpMax)
            tmpMax = cars[i].price;
    }
    return tmpMax;
}

int main(int argc, char const *argv[]) {

    return 0;
}
