/**
 * @file: PointerToArray.cpp
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
    /* Except when it is operand of the sizeof operator, the _Alignof operator, or the unary
       & operator, or is a string literal used to initialize an array, an expression that has
       type "array of type" is converted to an expression with type "pointer to type" that
       points to the initial element of the array object.
    */
    int a[4] = {1, 3, 5, 7};
    cout << a << endl;
    cout << a + 1 << endl;  // 跨越数组首元素，打印数组 a 中下一个元素的地址
    // 'a' is the name of the 'array a'. '&a' will return a pointer which points to this array.
    // &a 是指向整个数组 a 的指针。指针 &a 的管辖范围是整个数组，而指针 a 的管辖范围是数组是首元素
    cout << &a << endl;
    cout << &a + 1 << endl; // 会跨越整个数组，打印数组 a 之后的地址
    // If E is a pointer, (*E) will return the object which it points to.
    cout << *(&a) << endl;      // 相当于打印 a。
    cout << *(&a) + 1 << endl;  // 相当于打印 a+1

    // cout << &(a+1) << endl;  // error: cannot take the address of an rvalue of type 'int *'
}

void fun2()
{
    // Note: a[0] is the first element of a[3][4], a small of array. a points to a[0]
    int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    cout << "           a = " << a << endl;                     // the address of a[0]
    cout << "       &a[0] = " << &a[0] << endl << endl;         // the address of a[0]

    cout << "       a + 1 = " << a + 1 << endl;                 // the address of a[1]
    cout << "   &a[0] + 1 = " << &a[0] + 1 << endl << endl;     // the address of a[1]

    cout << "          *a = " << *a << endl;                    // the address of a[0][0]
    cout << "        a[0] = " << a[0] << endl;                  // the address of a[0][0]
    cout << "    &a[0][0] = " << &a[0][0] << endl << endl;      // the address of a[0][0]

    cout << "      *a + 1 = " << *a + 1 << endl;                // the address of a[0][1]
    cout << "    a[0] + 1 = " << a[0] + 1 << endl;              // the address of a[0][1]
    cout << "&a[0][0] + 1 = " << &a[0][0] + 1 << endl << endl;  // the address of a[0][1]
}

void fun3()
{
    int a[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    cout << "           a = " << a << endl;                     // the address of a[0]
    cout << "       &a[0] = " << &a[0] << endl << endl;         // the address of a[0]

    cout << "       a + 1 = " << a + 1 << endl;                 // the address of a[1]
    cout << "   &a[0] + 1 = " << &a[0] + 1 << endl << endl;     // the address of a[1]

    cout << "        a[1] = " << a[1] << endl;                  // the address of a[1][0]
    cout << "       &a[1] = " << &a[1] << endl;                 // the address of a[1]
    cout << "      *(a+1) = " << *(a+1) << endl << endl;        // the address of a[1][0]

    cout << "      *a + 1 = " << *a + 1 << endl << endl;        // the address of a[0][1]

    cout << "          &a = " << &a << endl;                // the address of the whole array a
    cout << "      &a + 1 = " << &a + 1 << endl;            // the address after array a
}

int main(int argc, char const *argv[]) {
    /* 数组名相当于指向数组第一个元素的指针
       &E 相当于把 E 的管辖范围上升了一个级别
       *E 相当于把 E 的管辖范围下降了一个级别
    */
    fun1();
    fun2();
    fun3();

    return 0;
}
