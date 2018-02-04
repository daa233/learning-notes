/**
 * @file: AssignmentOperatorOperatorOverloading.cpp
 * @description: 赋值运算符重载
 编写一个可变长的字符串类 MyString，其中：
 - 包含一个 char * 类型的成员变量，指向动态分配内存的存储空间
 - 该存储空间用于存放以 '\0' 结尾的字符串
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 18th, 2017
 */

#include <iostream>

class MyString {
private:
    char *str;
public:
    int id;     // for debugging
    MyString() : str(NULL) {}
    const char *c_str() {return str;}
    char *operator=(const char *s);
    MyString operator=(const MyString &s);
    MyString(const MyString &);
    ~MyString();
};

MyString::MyString(const MyString &s) {
    id = -s.id;
    if (s.str) {    // s is not NULL
        str = new char[strlen(s.str) + 1];  // + 1 for '\0'
        strcpy(str, s.str);
    } else {
        str = NULL;
    }
    std::cout << "id = " << s.id << " copy constructor is called. " << std::endl;
}

char *MyString::operator=(const char *s) {
    if (str) delete[] str;
    if (s) {    // s is not NULL
        str = new char[strlen(s) + 1];  // + 1 for '\0'
        strcpy(str, s);
    } else {
        str = NULL;
    }
    return str;
}

// deep copy
MyString MyString::operator=(const MyString &s) {
    if (str == s.str) return *this; // self-assignment
    if (str) delete[] str;
    str = new char[strlen(s.str) + 1];
    strcpy(str, s.str);
    return *this;   // to chain this operator, eg x = y = z
}

MyString::~MyString() {
    std::cout << "id = " << this->id << " destructor is called." << std::endl;
    if (str) delete[] str;
}

int main() {
    // no constructor MyString(char *)
    // error: no viable conversion from 'const char [11]' to 'MyString'
    // MyString s = "Good luck!";
    MyString s;
    s = "Good luck!";   // same as s.operator=("Good luck!");
    std::cout << s.c_str() << std::endl;    // Good luck!
    s = "Ocean University of China";
    s.id = 0;
    std::cout << s.c_str() << std::endl;    // Ocean University of China

    MyString s1, s2;
    s1 = "this";
    s1.id = 1;
    s2 = "that";
    s2.id = 2;
    // Note: here won't call char *operator=(const char *s); the types don't match!
    // So it will call the default operator= by the compiler, use shallow copy
    // s1 = s2; // runtime error:  pointer being freed was not allocated

    // after overloading the assignment operator MyString &MyString::operator=(const MyString &s);
    s1 = s2;    // OK

    // (s = s1) = s2;
    std::cout << "s = " << s.c_str() << std::endl;      // that
    std::cout << "s1 = " << s1.c_str() << std::endl;    // that
    std::cout << "s2 = " << s2.c_str() << std::endl;    // that
}
