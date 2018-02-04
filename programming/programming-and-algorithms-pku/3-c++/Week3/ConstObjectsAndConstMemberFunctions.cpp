/**
 * @file: ConstObjectsAndConstMemberFunctions.cpp
 * @description: 常量对象、常量成员函数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 15th, 2017
 */

#include <iostream>

class Demo {
private:
    int value;
public:
    Demo(int v) : value(v) {}
    void setValue(int v) {
        value = v;
    }
};

class Sample {
public:
    int value;
    Sample() {}
    int getValue() const;
    void func() {}
};

int Sample::getValue() const {
    // error: cannot assign to non-static data member within const member function 'getValue'
    // value = 0;
    // error: member function 'func' not viable: 'this' argument has type 'const Sample',
    // but function is not marked const
    // func();
    return value;
}

class CTest {
private:
    int n;
public:
    CTest() : n(1) {}
    int getValue() const {
        return n;
    }
    int getValue() {
        return 2 * n;
    }
};

int main(int argc, char const *argv[]) {
    const Demo obj(0); // const object
    // error: member function 'setValue' not viable: 'this' argument has type
    // 'const Demo', but function is not marked const
    // obj.setValue(1);

    const Sample o; // 大部分编译器需要为 Sample 类编写构造函数，然后才能
    // error: cannot assign to variable 'o' with const-qualified type 'const Sample'
    // o.value = 100;
    // error: member function 'func' not viable: 'this' argument has type 'const Sample',
    // but function is not marked const
    // o.func();
    std::cout << o.getValue() << std::endl;   // OK

    const CTest objTest1;
    CTest objTest2;
    std::cout << objTest1.getValue() << ", " << objTest2.getValue() << std::endl;   // 1, 2
    return 0;
}
