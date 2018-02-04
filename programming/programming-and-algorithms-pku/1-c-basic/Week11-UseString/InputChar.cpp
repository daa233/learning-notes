/**
 * @file: InputChar.cpp
 * @description: 字符串数组的使用以及字符的读取
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>
#include <cstdio>   // 为了使用EOF常量

using namespace std;

int main(int argc, char *argv[])
{
    char a[] = "China";     // 仅初始化时可以将一个字符串常量或字符数组直接赋给另一个字符串数组
    // char a[5] = "China"; // 不合法，数组a[]长度不够
    char b[] = {'C', 'h', 'i', 'n', 'a'};   // a[]比b[]末尾多了一个'\0'
    char c[8] = {'C', 'h', 'i', 'n', 'a'};  // c[]的后3位会被初始化为'\0'
    char d[8];  // 测试赋值是否合法，不合法赋值已注释，此数组未使用
    // char d[];   // 定义时不指明长度，不合法
    // d = "China"; // "China"是const char[6]型，不能赋值给char[8]型，不合法
    // d = c;       // 无效的字符串赋值，不合法
    // d[] = "China";   // 不合法
    // d[8] = "China";  // 不能完成从const char *到char型的类型转换，不合法

    // 测试cin, cin.get(), cin.get(char), getchar()，测试每一部分时，需要注释其他部分
    /*float grade = 0;
    // 在键盘输入数据，按下回车后，数据会首先送到输入缓存区，然后cin再从输入缓存区读取数据
    // cin会跳过空格和回车，把它们作为区分不同输入数据的标志
    while (cin >> grade) {  // 连续读入数据，如果不能读到float型数据会退出循环
        cout << grade << endl;
    }*/

    /* 在没有注释上面输入和打印grade的代码时，下面关于ch的代码总是无法运行。经过检查发现，在结束上面的循环——也就是输入一个不为float型
    的数据之后，cin.get()的返回值总是为-1。由此猜测，当cin读取不到指定的类型时，会用-1来代替。 */
    /*
    char ch = '0';
    while ((ch = cin.get()) != EOF) {   // EOF是文件结束标志，用于结束输入，可以由Ctrl+Z或Ctrl+D产生
        cout << ch;
    }
    */

    /*
    char ch = '0';
    while (cin.get(ch)) {   // cin.get(char)和cin.get()运行结果完全一样
        cout << ch;
    }
    */

    char ch = '0';
    // getchar()可以跳过任何字符。在Ubuntu终端测试Ctrl+D无法结束输入，但是Ctrl+Z和Ctrl+C可以
    while (ch = getchar()) {
        cout << ch;
    }

    return 0;
}
