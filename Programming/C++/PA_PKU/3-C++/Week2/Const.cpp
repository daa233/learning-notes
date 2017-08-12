/**
 * @file: Const.cpp
 * @description: const 关键字的用法
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

void myPrintf(const char *p)
{
    // error: no matching function for call to 'strcpy'
    // note: candidate function not viable: 1st argument ('const char *') would lose const qualifier
    // char    *strcpy(char *__dst, const char *__src);
    // strcpy(p, "this");
    cout << p << endl;
}

int main(int argc, char const *argv[]) {
    // 定义常量
    const int MAX_VAL = 23;
    const double PI = 3.14;
    const char *SCHOOL_NAME = "Ocean University of China";

    // 定义常量指针
    int n, m;
    const int *p = &n;
    // *p = 5;  // error: read-only variable is not assignable
    n = 4;      // right
    p = &m;     // right

    // 不能把常量指针赋给非常量指针（除非强制类型转换），反过来可以
    const int *p1;
    int *p2;
    p1 = p2;    // right
    // p2 = p1;    // error: assigning to 'int *' from incompatible type 'const int *'
    p2 = (int *)p1; // right, cast type

    // 定义常引用
    // 不能通过常引用修改其引用的变量
    const int &r = n;
    // r = 5;  // error: cannot assign to variable 'r' with const-qualified type 'const int &'
    n = 4;
    return 0;
}
