/**
 * @file: TestSwitchForLoop.cpp
 * @description: for语句中嵌套switch语句，使用break时跳出哪一层？
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                cout << i << endl;
                break;
            case 1:
                cout << i << endl;
                break;
            case 2:
                cout << i << endl;
                break;
            default:
                break;
        }
        // break语句仅跳出了switch，没有跳出switch外部的循环下面这句话可以打印出来
        cout << "If you see this, the break didn't jumped out the for-loop.\n";
        if (true) {
            break;  // if语句中的switch语句会跳出if语句外的循环
        }
        cout << "I think you can't see this." << endl;
    }
    return 0;
}
