/**
 * @file: PointerIncrement.cpp
 * @description: p为指针变量，p++代表什么？
 *
 * @author: Du Ang
 * @date: Apr. 21st, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int i = 0;
    float f = 1.0;
    char c = 'b';
    int *p1 = &i;
    float *p2 = &f;
    char *p3 = &c;
    cout << "The addresses before increment:" << endl;
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    // C++标准库中I/O类对输出操作符<<进行了重载，在遇到字符型指针时会将其当做字符串名来处理，输出指针所指的字符串。
    // 参考：http://blog.csdn.net/sszgg2006/article/details/7982866
    // cout << "p3 = " << p3 << endl;  // 输出结果为“p3 = a”
    // 将char *类型强制转换为void *类型，防止p3作为字符串数组被打印。或者使用C中printf的格式控制来打印p3的值
    cout << "p3 = " << static_cast<void*>(p3) << endl;

    p1++; p2++; p3++;
    cout << "The addresses after increment:" << endl;
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << static_cast<void*>(p3) << endl;
    return 0;
}
