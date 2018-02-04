/**
 * 类和对象 编程题＃2
 *
 * @file: Week3Ex2.cpp
 * @description: 程序填空
                下面程序的输出是：10
                请补足Sample类的成员函数。不能增加成员变量。
 * @input:

 * @output: 
    10
 * @sample_input:

 * @sample_output:
    10
 *
 * @author: Du Ang
 * @date: Aug. 15th, 2017
 */

#include <iostream>
using namespace std;
class Sample{
public:
    int v;
    Sample(int n):v(n) { }
    // 在此处补充你的代码
    Sample(const Sample &obj) {
        v = obj.v * 2;
    }
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}
