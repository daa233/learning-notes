#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

void f1()
{
    char str1[] = {'H', 'e', 'l', 'l', 'o'};       // invalid
    char str2[] = {'H', 'e', 'l', 'l', 'o', '\0'}; // valid
    char str3[] = "Hello";
    char str4[] = "Hello\0";
    char str5[10] = {'H', 'e', 'l', 'l', 'o'};
    char str6[10] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char str7[10] = "Hello";
    char str8[10] = "Hello\0";
    char *str9 = "Hello"; // warning: conversion from string literal to 'char *'

    cout << str1 << endl; // HelloHello (undefined)
    cout << str2 << endl; // Hello
    cout << str3 << endl; // Hello
    cout << str4 << endl; // Hello
    cout << str5 << endl; // Hello
    cout << str6 << endl; // Hello
    cout << str7 << endl; // Hello
    cout << str8 << endl; // Hello
    cout << str9 << endl; // Hello

    cout << strlen(str1) << endl; // 10 (undefined)
    cout << strlen(str2) << endl; // 5
    cout << strlen(str3) << endl; // 5
    cout << strlen(str4) << endl; // 5
    cout << strlen(str5) << endl; // 5
    cout << strlen(str6) << endl; // 5
    cout << strlen(str7) << endl; // 5
    cout << strlen(str8) << endl; // 5
    cout << strlen(str9) << endl; // 5

    cout << sizeof(str1) << endl; // 5
    cout << sizeof(str2) << endl; // 6
    cout << sizeof(str3) << endl; // 6
    cout << sizeof(str4) << endl; // 7
    cout << sizeof(str5) << endl; // 10
    cout << sizeof(str6) << endl; // 10
    cout << sizeof(str7) << endl; // 10
    cout << sizeof(str8) << endl; // 10
    cout << sizeof(str9) << endl; // 8, pointer type size
}

void f2()
{
    char str1[][10] = {"Apple", "Banana", "Car"};
    // char str2[][] = {"Apple", "Banana", "Car"};  // invalid
    char *str2[10] = {"Apple", "Banana", "Car"}; // warning: conversion from string literal to 'char *'
    char *str3[] = {"Apple", "Banana", "Car"};   // warning: conversion from string literal to 'char *'

    cout << *str1 << endl;   // Apple
    cout << *str2 << endl;   // Apple
    cout << str1[0] << endl; // Apple
    cout << str2[0] << endl; // Apple

    cout << strlen(*str1) << endl;   // 5
    cout << strlen(*str2) << endl;   // 5
    cout << strlen(str1[0]) << endl; // 5
    cout << strlen(str2[0]) << endl; // 5

    cout << sizeof(str1) << endl; // 30
    cout << sizeof(str2) << endl; // 80
    cout << sizeof(str3) << endl; // 24

    cout << sizeof(*str1) << endl; // 10
    cout << sizeof(*str2) << endl; // 8
    cout << sizeof(*str3) << endl; // 2
}

// Refers to https://blog.csdn.net/zkk9527/article/details/90181505
void f3()
{
    char *str[] = {"Welcome", "to", "Fortemedia", "Nanjing"};
    char **p = str + 1;
    str[0] = (*p++) + 2;
    str[1] = *(p + 1);
    str[2] = p[1] + 3;
    str[3] = p[0] + (str[2] - str[1]);

    cout << str[0] << endl;     // ('\0' after "to", no output)
    cout << str[1] << endl;     // Nanjing
    cout << str[2] << endl;     // jing
    cout << str[3] << endl;     // g
}

int main()
{
    // f1();
    // f2();
    f3();
    return 0;
}
