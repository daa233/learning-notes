/**
 * @file: FunctionsWithArray.cpp
 * @description: 数组与函数
 *              分别测试用数组元素和数组名作为函数参数
 *
 * @author: Du Ang
 * @date:  Aug. 2nd, 2017
 */

#include <iostream>

using namespace std;

void changeByElement(int a, int b)
{
    a = 30;
    b = 50;
}

void changeByArrayName(int a[])
{
    a[0] = 30;
    a[1] = 50;
}

int main(int argc, char const *argv[]) {
    int a[2] = {3, 5};
    changeByElement(a[0], a[1]);
    cout << a[0] << " " << a[1] << endl;    // 3 5
    a[0] = 3;
    a[1] = 5;
    changeByArrayName(a);
    cout << a[0] << " " << a[1] << endl;    // 30 50
    return 0;
}
