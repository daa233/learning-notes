/**
 * @file: ClassTemplateSpecialization.cpp
 * @description: 类模板的特化
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>

using namespace std;

template <class T>
class MyClass {
public:
    MyClass(T x) {
        cout << x << " - not a char" << endl;
    }
};

template <>
class MyClass<char> {
public:
    MyClass(char x) {
        cout << x << " is a char!" << endl;
    }
};

int main(int argc, char const *argv[]) {
    MyClass<int> obj1(42);          // 42 - not a char
    MyClass<double> obj2(5.47);     // 5.47 - not a char
    MyClass<char> obj3('s');        // s is a char!
    return 0;
}
