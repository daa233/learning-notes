/**
 * @file: StaticLocalVar.cpp
 * @description: 静态局部变量
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>

using namespace std;

void fun()
{
    int a = 0;
    static int b = 0;

    a = a + 1;
    b = b + 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

int main(int argc, char const *argv[]) {
    for (int i = 0; i < 5; i++) {
        fun();
        cout << "Call again!" << endl;
    }
    return 0;
}
