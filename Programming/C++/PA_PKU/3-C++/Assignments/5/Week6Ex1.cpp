/**
 *  多态与虚函数 编程题＃1
 *
 * @file: Week6Ex1.cpp
 * @description: 程序填空
                下面程序的输出结果是：
                    A::Fun
                    C::Do
 * @sample_input:
    none
 * @sample_output:
    A::Fun
    C::Do
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

class A {
private:
    int nVal;
public:
    void Fun()
    { cout << "A::Fun" << endl; }
    void Do()
    { cout << "A::Do" << endl; }
};

class B : public A {
public:
    virtual void Do()
    { cout << "B::Do" << endl; }
};

class C : public B {
    public:
    void Do( )
    { cout << "C::Do" <<endl; }
    void Fun()
    { cout << "C::Fun" << endl; }
};

void Call(
    // 在此处补充你的代码
    B &p
         )  {
    p.Fun();
    p.Do();
}
int main()  {
    C c;
    Call(c);
    return 0;
}
