/**
 *  多态与虚函数 编程题＃2
 *
 * @file: Week6Ex2.cpp
 * @description: 程序填空
                下面程序的输出结果是：
                    destructor B
                    destructor A
                请完整写出 class A。
                限制条件：不得为 class A 编写构造函数。
 * @sample_input:
    none
 * @sample_output:
    destructor B
    destructor A
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

class A {
    // 在此处补充你的代码
public:
    virtual ~A() { cout << "destructor A" << endl; }
};

class B : public A {
public:
    ~B() { cout << "destructor B" << endl; }
};

int main() {
    A * pa;
    pa = new B;
    delete pa;
    return 0;
}
