/**
 * @file: MultiSetSample.cpp
 * @description: STL 中 multiset 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <set>

using namespace std;

template <class T>
void print(T first, T last) {
    for ( ; first != last; ++first) {
        cout << *first << " ";
    }
    cout << endl;
}

class A {
private:
    int n;
public:
    A(int n_) { n = n_; }
    friend bool operator<(const A &a1, const A &a2) {
        return a1.n < a2.n;
    }
    friend ostream &operator<<(ostream &o, const A &a2) {
        o << a2.n;
        return o;
    }
    friend class MyLess;
};

struct MyLess {
    bool operator()(const A &a1, const A &a2) {
        return (a1.n % 10) < (a2.n % 10);   // compare by the single digit
    }
};

typedef multiset<A> MSET1;
typedef multiset<A, MyLess> MSET2;

int main() {
    const int SIZE = 6;
    A a[SIZE] = {4, 22, 19, 8, 33, 40};
    MSET1 m1;
    m1.insert(a, a + SIZE);
    m1.insert(22);
    cout << "1) " << m1.count(22) << endl;
    // 1) 2
    cout << "2) ";
    print(m1.begin(), m1.end());
    // 2) 4 8 19 22 22 33 40
    MSET1::iterator pp = m1.find(19);
    if (pp != m1.end()) {
        cout << "found " << *pp << endl;    // found 19
    }
    cout << "3) ";
    cout << *m1.lower_bound(22) << ", " << *m1.upper_bound(22) << endl;
    // 3) 22, 33
    // delete all elements in [m1.lower_bound(22), m1.upper_bound(22))
    // after deleting, pp will point to m1.upper_bound(22)
    pp = m1.erase(m1.lower_bound(22), m1.upper_bound(22));
    cout << "4) ";
    print(m1.begin(), m1.end());
    // 4) 4 8 19 33 40
    cout << "5) ";
    cout << *pp << endl;
    // 5) 33
    MSET2 m2;   // m2 elemets is sorted by the single digit
    m2.insert(a, a + SIZE);
    cout << "6) ";
    print(m2.begin(), m2.end());
    return 0;
}
