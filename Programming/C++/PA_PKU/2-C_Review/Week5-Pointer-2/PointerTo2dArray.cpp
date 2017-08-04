/**
 * @file: PointerTo2dArray.cpp
 * @description: 二维数组与指针
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 4th, 2017
 */

#include <iostream>

using namespace std;

void fun1()
{
    int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    cout << "           a = " << a << endl;
    cout << "       &a[0] = " << &a[0] << endl << endl;

    cout << "       a + 1 = " << a + 1 << endl;
    cout << "   &a[0] + 1 = " << &a[0] + 1 << endl << endl;

    cout << "          *a = " << *a << endl;
    cout << "        a[0] = " << a[0] << endl;
    cout << "    &a[0][0] = " << &a[0][0] << endl << endl;

    cout << "      *a + 1 = " << *a + 1 << endl;
    cout << "    a[0] + 1 = " << a[0] + 1 << endl;
    cout << "&a[0][0] + 1 = " << &a[0][0] + 1 << endl << endl;
}

void fun2()
{
    int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    cout << "           a = " << a << endl;
    cout << "       &a[0] = " << &a[0] << endl << endl;

    cout << "       a + 1 = " << a + 1 << endl;
    cout << "   &a[0] + 1 = " << &a[0] + 1 << endl << endl;

    cout << "        a[1] = " << a[1] << endl;
    cout << "       &a[1] = " << &a[1] << endl;
    cout << "      *(a+1) = " << *(a+1) << endl << endl;

    cout << "      *a + 1 = " << *a + 1 << endl << endl;

    cout << "          &a = " << &a << endl;
    cout << "      &a + 1 = " << &a + 1 << endl;
}

int main(int argc, char const *argv[]) {
    /* 数组名相当于指向数组第一个元素的指针
       &E 相当于把 E 的管辖范围上升了一个级别
       *E 相当于把 E 的管辖范围下降了一个级别
    */
    fun1();
    fun2();
    return 0;
}
