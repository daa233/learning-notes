/**
 * @file: FunctionTemplatesCallPriority.cpp
 * @description: 函数模板的调用顺序
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

template <class T>
T myMax(T a, T b) {
    cout << "template 1 is called" << endl;
    return 0;
}

template <class T1, class T2>
T1 myMax(T1 a, T2 b) {
    cout << "template 2 is called" << endl;
    return 0;
}

double myMax(double a, double b) {
    cout << "normal myMax is called" << endl;
    return 0;
}

int main(int argc, char const *argv[]) {
    int i = 4, j = 5;
    myMax(1.2, 3.4);    // normal myMax is called
    myMax(i, j);        // template 1 is called
    myMax(1.2, 3);      // template 2 is called
    return 0;
}
