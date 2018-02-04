/**
 * 类和对象 编程题＃1
 *
 * @file: Week3Ex1.cpp
 * @description: 程序填空
 * @input:

 * @output: 
    0
    5
 * @sample_input:

 * @sample_output:
    0
    5
 * @hint: 所缺代码具有如下形式：
    A(_________________ ){ val = n; }
    ________________ GetObj() {
        return _________________;
    }
 * @author: Du Ang
 * @date: Aug. 15th, 2017
 */

#include <iostream>

using namespace std;

class A {
public:
    int val;
    // 在此处补充你的代码
    A(int n = 0) : val(n) {}    // 根据提示，参数表应含有 n，又因为可以通过无参构造，参数 n 默认为 0
    int &GetObj() { // 赋值符号左边一定是个变量级别的，不能是指针或地址
        return val;
    }
};

int main()  {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
    return 0;
}
