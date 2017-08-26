/**
 * @file: ClassTemplatePair.cpp
 * @description: Pair 类模板 Pair，可以用于存放一个键值对
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

template <class T1, class T2>
class Pair {
public:
    T1 key;
    T2 value;
    Pair(T1 k, T2 v) : key(k), value(v) {};
    bool operator<(const Pair<T1, T2> &p) const;
};

template <class T1, class T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2> &p) const {
    return key < p.key;
}

int main(int argc, char const *argv[]) {
    Pair<string, int> student("Tom", 19);
    cout << student.key << " " << student.value << endl;    // Tom 19
    return 0;
}
