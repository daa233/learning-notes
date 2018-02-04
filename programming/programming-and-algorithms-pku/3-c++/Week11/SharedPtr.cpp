/**
 * @file: SharedPtr.cpp
 * @description: C++11 新特性，智能指针 shared_ptr
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>
#include <memory>   // shared_ptr

using namespace std;

struct A {
    int n;
    A(int v = 0) : n(v) {}
    ~A() {
        cout << n << " destructor" << endl;
    }
};

struct B {
    ~B() {
        cout << "~B" << endl;
    }
};

int main(int argc, char const *argv[]) {
    shared_ptr<A> sp1(new A(2));    // sp1 owns A(2)
    shared_ptr<A> sp2(sp1);         // sp2 owns A(2) too
    cout << "1) " << sp1->n << ", " << sp2->n << endl;  // 1) 2, 2
    shared_ptr<A> sp3;
    A *p = sp1.get();               // p gets the pointer sp1 owns, i.e. A(2)
    cout << "2) " << p->n << endl;  // 2) 2
    sp3 = sp1;                      // sp3 owns A(2) too
    cout << "3) " << (*sp3).n << endl;  // 3) 2
    sp1.reset();                    // sp1 doesn't own A(2) anymore
    if (!sp1) {
        cout << "4) sp1 is null" << endl;   // 4) sp1 is null
    }
    A *q = new A(3);
    sp1.reset(q);                   // sp1 owns q, i.e. A(3)
    cout << "5) " << sp1->n << endl;        // 5) 3
    shared_ptr<A> sp4(sp1);         // sp4 owns A(3)
    sp1.reset();                    // sp1 doesn't own A(3) anymore
    cout << "before end main" << endl;
    sp4.reset();                    // sp4 doesn't own A(3) anymore
    // 3 destructor
    cout << "end main" << endl;
    // 2 destructor

    B *pointer = new B();
    shared_ptr<B> ptr(pointer);
    shared_ptr<B> ptr2;
    // reset won't increase the count of pointer in ptr
    // the program will crash because pointer will be deleted twice
    // ptr2.reset(pointer);
    cout << "end" << endl;
    // ~B
    // ~B
    return 0;
}
