/**
 * @file: AssignmentOperatorOperatorOverloadingTest.cpp
 * @description: 赋值运算符重载 （来源于 LearnCpp.com）
                编写一个可变长的字符串类 MyString
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 18th, 2017
 */

#include <iostream>

class MyString {
private:
    char *m_data;
    int m_length;
public:
    MyString(const char *data = "", int length = 0) : m_length(length) {
        if (!length)
            m_data = nullptr;
        else
            m_data = new char[length];

        for (int i = 0; i < length; ++i) {
            m_data[i] = data[i];
        }
    }

    // Overload assignment
    MyString &operator=(const MyString &str);

    friend std::ostream &operator<<(std::ostream &out, const MyString &s);
};

std::ostream &operator<<(std::ostream &out, const MyString &s) {
    out << s.m_data;
    return out;
}

// A simplistic implementation of operator= (do not use)
MyString &MyString::operator=(const MyString &str) {
    // self-assignment guard
    if (this == &str)
       return *this;

    // if data exists in the current string, delete it
    if (m_data) delete[] m_data;
    // std::cout << "the address of str.m_data = " << static_cast<void *>(str.m_data) << std::endl;
    // std::cout << "the address of (*this).m_data = " << static_cast<void *>((*this).m_data)
    //         << std::endl;
    // same addresses

    m_length = str.m_length;

    // some dummy operations that will allocate memory
    char *dummy = new char[10];
    for (int i = 0; i < 9; i++) {
        dummy[i] = 'A';
    }
    dummy[9] = '\0';
    delete[] dummy;

    // copy the data from str to the implicit object
    m_data = new char[str.m_length];

    for (int i=0; i < str.m_length; ++i)
        m_data[i] = str.m_data[i];

    // return the existing object so we can chain this operator
    return *this;
}

int main(int argc, char const *argv[]) {
    MyString alex("Alex", 5);
    // use the custom assignment operator
    MyString employee;
    employee = alex;
    std::cout << employee << std::endl; // Alex

    // self-assignment
    alex = alex;
    std::cout << alex << std::endl;     // Alex
    return 0;
}
