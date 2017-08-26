/**
 * @file: ClassTemplatesInheritanceAndDerived.cpp
 * @description: 类模板的继承与派生
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>
#include <typeinfo>

using namespace std;

/***** 1. Class template derived from class templates *****/
template <class T1, class T2>
class A1 {
protected:  // private members can't be directly accessed by derived class
    T1 v1;
    T2 v2;
public:
    A1(T1 val1, T2 val2) : v1(val1), v2(val2) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        // execute 'a.out | c++fill' to get right display of 'name'
        cout << "T1 v1: " << typeid(v1).name() << " " << v1 << endl;
        cout << "T2 v2: " << typeid(v2).name() << " " << v2 << endl;
    }
};

template <class T1, class T2>
class A2 : public A1<T2, T1> {    // note the sequence of T1 and T2
protected:
    T1 v3;
    T2 v4;
public:
    // note there is <T2, T1> after A1 in the member initializer
    A2(T2 val1, T1 val2, T1 val3, T2 val4) : A1<T2, T1>(val1, val2), v3(val3), v4(val4) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        // need to use this pointer to access v1, v2. see:
        // https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-members
        // https://stackoverflow.com/questions/24158209/
        cout << "T2 v1: " << typeid(this->v1).name() << " " << this->v1 << endl;
        cout << "T1 v2: " << typeid(this->v2).name() << " " << this->v2 << endl;
        cout << "T1 v3: " << typeid(v3).name() << " " << v3 << endl;
        cout << "T2 v4: " << typeid(v4).name() << " " << v4 << endl;
    }
};
/******************************************************/

/***** 2. Class template derived from template classes *****/
template <class T1, class T2>
class B1 {
protected:
    T1 v1;
    T2 v2;
public:
    B1(T1 val1, T2 val2) : v1(val1), v2(val2) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        cout << "T1 v1: " << typeid(v1).name() << " " << v1 << endl;
        cout << "T2 v2: " << typeid(v2).name() << " " << v2 << endl;
    }
};

template <class T>
class B2 : public B1<int, double> {
private:
    T v3;
public:
    B2(int val1, double val2, T val3) : B1(val1, val2), v3(val3) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        // no need to use this pointer to access v1, v2 here
        cout << "int v1: " << typeid(v1).name() << " " << v1 << endl;
        cout << "double v2: " << typeid(v2).name() << " " << v2 << endl;
        cout << "T3 v3: " << typeid(v3).name() << " " << v3 << endl;
    }
};
/******************************************************/

/***** 3. Class template derived from normal classes *****/
class C1 {
protected:
    int v1;
public:
    C1(int val1) : v1(val1) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        cout << "int v1: " << typeid(v1).name() << " " << v1 << endl;
    }
};

template <class T>
class C2 : public C1 {
private:
    T v2;
public:
    C2(int val1, T val2) : C1(val1), v2(val2) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        cout << "int v1: " << typeid(v1).name() << " " << v1 << endl;
        cout << "T v2: " << typeid(v2).name() << " " << v2 << endl;
    }
};
/******************************************************/

/***** 4. Normal class derived from template classes *****/
template <class T>
class D1 {
protected:
    T v1;
    int v2;
public:
    D1(T val1, int val2) : v1(val1), v2(val2) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        cout << "T v1: " << typeid(v1).name() << " " << v1 << endl;
        cout << "int v2: " << typeid(v2).name() << " " << v2 << endl;
    }
};

class D2 : public D1<int> {
private:
    double v3;
public:
    D2(int val1, int val2, double val3) : D1(val1, val2), v3(val3) {
        cout << "Class: " << typeid(*this).name() << endl;
    }
    void printMemberVarsTypes() {
        cout << "int v1: " << typeid(v1).name() << " " << v1 << endl;
        cout << "int v2: " << typeid(v2).name() << " " << v2 << endl;
        cout << "double v3: " << typeid(v3).name() << " " << v3 << endl;
    }
};
/******************************************************/

int main(int argc, char const *argv[]) {
    /***** 1. Class template derived from class templates *****/
    A1<int, double> a1(1, 2.0);         // int v1, double v2
    // Class: A1<int, double>
    a1.printMemberVarsTypes();
    // T1 v1: int 1
    // T2 v2: double 2
    A2<int, double> a2(3.0, 4, 5, 6.0); // double v1, int v2, int v3, double v4
    // Class: A1<double, int>
    // Class: A2<int, double>
    a2.printMemberVarsTypes();
    // T2 v1: double 3
    // T1 v2: int 4
    // T1 v3: int 5
    // T2 v4: double 6
    /******************************************************/

    /***** 2. Class template derived from template classes *****/
    B1<double, bool> b1(1.0, true);
    // Class: B1<double, bool>
    b1.printMemberVarsTypes();
    // T1 v1: double 1
    // T2 v2: bool 1
    B2<char> b2(3, 4.0, 'E');
    // Class: B1<int, double>
    // Class: B2<char>
    b2.printMemberVarsTypes();
    // int v1: int 3
    // double v2: double 4
    // T3 v3: char E
    /******************************************************/

    /***** 3. Class template derived from normal classes *****/
    C1 c1(1);
    // Class: C1
    c1.printMemberVarsTypes();
    // int v1: int 1
    C2<char> c2(2, 'C');
    // Class: C1
    // Class: C2<char>
    c2.printMemberVarsTypes();
    // int v1: int 2
    // T v2: char C
    /******************************************************/

    /***** 4. Normal class derived from template classes *****/
    D1<char> d1('A', 2);
    // Class: D1<int>
    d1.printMemberVarsTypes();
    // T v1: char A
    // int v2: int 2
    D2 d2(3, 4, 5);
    // Class: D1<int>
    // Class: D2
    d2.printMemberVarsTypes();
    // int v1: int 3
    // int v2: int 4
    // double v3: double 5
    /******************************************************/
    return 0;
}
