/**
 * @file: ListSample.cpp
 * @description: list 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 29th, 2017
 */

#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

class A {
private:
    int n;
public:
    A (int n_) { n = n_; }
    friend bool operator<(const A &a1, const A &a2);
    friend bool operator==(const A &a1, const A &a2);
    friend ostream &operator<<(ostream &out, const A &a);
};

bool operator<(const A &a1, const A &a2) {
    return a1.n < a2.n;
}

bool operator==(const A &a1, const A &a2) {
    return a1.n == a2.n;
}

ostream &operator<<(ostream &o, const A &a) {
    o << a.n;
    return o;
}

template <class T>
void printList(const list<T> &lst) {
    int tmp = lst.size();
    if (tmp > 0) {
        // use typename to demonstrate that list<T>::const_iterator
        // is the name in this type. can ignore it in VC++
        typename list<T>::const_iterator i;
        i = lst.begin();
        for (i = lst.begin(); i != lst.end(); i++) {
            cout << *i << ", ";
        }
    }
}

int main() {
    list<A> lst1, lst2;
    lst1.push_back(1);
    lst1.push_back(3);
    lst1.push_back(2);
    lst1.push_back(4);
    lst1.push_back(2);

    lst2.push_back(10);
    lst2.push_front(20);
    lst2.push_back(30);
    lst2.push_back(30);
    lst2.push_back(30);
    lst2.push_front(40);
    lst2.push_back(40);

    cout << "1) ";
    printList(lst1);
    // 1) 1, 3, 2, 4, 2,
    cout << endl;
    cout << "2) ";
    printList(lst2);
    // 2) 40, 20, 10, 30, 30, 30, 40,
    cout << endl;
    // the sort function of list container, sort from the smallest to the largest
    lst2.sort();
    cout << "3) ";
    printList(lst2);
    // 3) 10, 20, 30, 30, 30, 40, 40,
    cout << endl;
    lst2.pop_front();
    cout << "4) ";
    printList(lst2);
    // 4) 20, 30, 30, 30, 40, 40,
    cout << endl;
    lst1.remove(2);     // delete all the elements that are equivalent to A(2)
    cout << "5) ";
    printList(lst1);
    // 5) 1, 3, 4,
    cout << endl;
    // erases all but the first element from every consecutive group of equal elements.
    lst2.unique();
    cout << "6) ";
    printList(lst2);
    // 6) 20, 30, 40,
    cout << endl;
    lst1.merge(lst2);   // merge lst2 to lst1, and clear lst2
    cout << "7) ";
    printList(lst1);
    // 7) 1, 3, 4, 20, 30, 40,
    cout << endl;
    cout << "8) ";
    printList(lst2);
    // 8)
    cout << endl;
    lst1.reverse();
    cout << "9) ";
    printList(lst1);
    // 9) 40, 30, 20, 4, 3, 1,
    cout << endl;
    lst2.push_back(100);
    lst2.push_back(200);
    lst2.push_back(300);
    lst2.push_back(400);
    cout << "10) ";
    printList(lst2);
    // 10) 100, 200, 300, 400,
    cout << endl;
    list<A>::iterator p1, p2, p3;
    p1 = find(lst1.begin(), lst1.end(), 3);
    p2 = find(lst2.begin(), lst2.end(), 200);
    p3 = find(lst2.begin(), lst2.end(), 400);
    // inserts elements into lst1 and removes them from lst2
    lst1.splice(p1, lst2, p2, p3);
    cout << "11) ";
    printList(lst1);
    cout << endl;
    cout << "12) ";
    printList(lst2);
    cout << endl;
}
