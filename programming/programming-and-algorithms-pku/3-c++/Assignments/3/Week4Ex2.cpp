/**
 *  运算符重载 编程题＃2
 *
 * @file: Week4Ex2.cpp
 * @description: 程序填空
                下面的 MyInt 类只有一个成员变量。MyInt 类内部的部分代码被隐藏了。假设下面的程序能编译通过，且输出
                结果是: 4,1
                请写出被隐藏的部分。（您写的内容必须是能全部放进 MyInt 类内部的，MyInt 的成员函数里不允许使用静态
                变量）。
 * @sample_input:
    none
 * @sample_output:
    4,1
 *
 * @author: Du Ang
 * @date: Aug. 21st, 2017
 */

#include <iostream>

using namespace std;

class MyInt {
    int nVal;
public:
    MyInt(int n) { nVal = n; }
    int ReturnVal() { return nVal; }
    // 在此处补充你的代码
    MyInt &operator-(int n) {   // operator - overloading
        nVal = nVal - n;
        return *this;
    }
};

int main ()  {
    MyInt objInt(10);
    objInt-2-1-3;
    cout << objInt.ReturnVal();
    cout <<",";
    objInt-2-1;
    cout << objInt.ReturnVal();
    return 0;
}
