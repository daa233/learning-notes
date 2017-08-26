/**
 * @file: UseString.cpp
 * @description: string 的一些特性
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    string s1("hello world");
    cout << s1.capacity() << endl;  // 22
    cout << s1.max_size() << endl;  // 18446744073709551599
    cout << s1.size() << endl;      // 11
    cout << s1.length() << endl;    // 11
    cout << s1.empty() << endl;     // 0
    cout << s1 << "aaa" << endl;    // hello worldaaa
    s1.resize(s1.length() + 10);
    cout << s1.capacity() << endl;  // 22
    cout << s1.max_size() << endl;  // 18446744073709551599
    cout << s1.size() << endl;      // 21
    cout << s1.length() << endl;    // 21
    cout << s1 << "aaa" << endl;    // hello worldaaa
    s1.resize(0);
    cout << s1.empty() << endl;     // 1

    s1 = "hello worlld";    // note it's worlld, not world
    cout << s1.find("ll") << endl;      // 2
    cout << s1.find("abc") << endl;     // 18446744073709551615
    cout << s1.rfind("ll") << endl;     // 9
    cout << s1.rfind("abc") << endl;    // 18446744073709551615
    cout << s1.find_first_of("abcde") << endl;  // 1
    cout << s1.find_first_of("abc") << endl;    // 18446744073709551615
    cout << s1.find_last_of("abcde") << endl;   // 11
    cout << s1.find_last_of("abc") << endl;     // 18446744073709551615
    cout << s1.find_first_not_of("abcde") << endl;          // 0
    cout << s1.find_first_not_of("hello world") << endl;    // 18446744073709551615
    cout << s1.find_last_not_of("abcde") << endl;           // 10
    cout << s1.find_last_not_of("hello world") << endl;     // 18446744073709551615

    s1 = "hello worlld";
    s1.erase(5);    // erase the content after index 5 of s1
    cout << s1 << endl;                 // hello
    cout << s1.length() << endl;        // 5
    cout << s1.size() << endl;          // 5

    s1 = "hello worlld";
    cout << s1.find("ll", 1) << endl;   // 2
    cout << s1.find("ll", 2) << endl;   // 2
    cout << s1.find("ll", 3) << endl;   // 9

    s1 = "hello worlld";
    s1.replace(2, 3, "haha");
    cout << s1 << endl;                 // hehaha worlld
    s1 = "hello worlld";
    s1.replace(2, 3, "haha", 1, 2);
    cout << s1 << endl;                 // heah worlld

    s1 = "hello world";
    string s2("show insert");
    s1.insert(5, s2);
    cout << s1 << endl;         // helloshow insert world
    s1.insert(2, s2, 5, 3);
    cout << s1 << endl;         // heinslloshow insert world

    s1 = "hello world";
    printf("%s\n", s1.c_str()); // hello world

    s1 = "hello world";
    const char *p1 = s1.data();
    for (int i = 0; i < s1.length(); i++) {
        printf("%c", *(p1 + i));
    }                           // hello world
    cout << endl;

    s1 = "hello world";
    int len = s1.length();
    char *p2 = new char[len+1];
    s1.copy(p2, 5, 0);
    p2[5] = 0;
    cout << p2 << endl;         // hello
    return 0;
}
