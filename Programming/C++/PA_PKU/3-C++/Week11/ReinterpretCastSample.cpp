/**
 * @file: ReinterpretCastSample.cpp
 * @description: reinterpret_cast 示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>

using namespace std;

class A {
public:
    int i;
    int j;
    A(int n) : i(n), j(n) {}
};

int main(int argc, char const *argv[]) {
    A a(100);
    int &r = reinterpret_cast<int &>(a);    // force to cast r to the reference of a
    r = 200;                                // a.i = 200
    cout << a.i << ", " << a.j << endl;     // 200, 100
    int n = 300;
    A *pa = reinterpret_cast<A *>(&n);      // force to cast pa points to n
    pa->i = 400;                            // n = 400
    pa->j = 500;                            // dangerous
    cout << n << endl;                      // 400
    long long la = 0x12345678abcdLL;
    // pa = reinterpret_cast<A *>(la);
    // error: cast from pointer to smaller type 'unsigned int' loses information
    // unsigned int u = reinterpret_cast<unsigned int>(pa);
    // cout << hex << u << endl;
    typedef void (*PF1)(int);               // function pointer
    typedef int (*PF2)(int, char *);
    PF1 pf1;
    PF2 pf2;
    pf2 = reinterpret_cast<PF2>(pf1);
    return 0;
}
