/**
 * @file: PointerToString.cpp
 * @description: 字符串与指针
 *
 * @author: Du Ang
 * @date:  Aug. 3rd, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

void fun1()
{
    char a[] = "How are you?", b[20];
    char *p1, *p2;
    for (p1 = a, p2 = b; *p1 != '\0'; p1++, p2++) {
        *p2 = *p1;
    }
    *p2 = '\0';
    cout << "string a is: " << a << endl;
    cout << "string b is: " << b << endl;
    cout << endl;
}

void fun2()
{
    int a = 5;
    int *pa = &a;

    int b[6] = {1, 2, 3, 4, 5, 6};
    int *pb = b;

    char c[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char *pc = c;

    cout << a << endl;          // 5
    cout << pa << endl << endl; // variable a's address

    cout << b << endl;          // the array b's address
    cout << pb << endl << endl; // the array b's address

    cout << c << endl;          // hello
    cout << pc << endl << endl; // hello

    cout << static_cast<void*>(c) << endl;  // the array c's address
    cout << static_cast<void*>(pc) << endl; // the array c's address
    cout << endl;
}

void fun3()
{
    char buffer[10] = "ABC";
    char *pc;
    // Warning: conversion from string literal to 'char *' is deprecated
    pc = "hello";   // "hello" is a string constant. Can't alter it by pc.

    cout << pc << endl;     // hello
    pc++;
    cout << pc << endl;     // ello
    cout << *pc << endl;    // e
    pc = buffer;
    cout << pc;             // ABC
    cout << endl;
}

int main(int argc, char const *argv[]) {
    fun1();
    fun2();
    fun3();
    
    return 0;
}
