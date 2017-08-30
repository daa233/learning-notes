/**
 * @file: ValueChangingCopySample.cpp
 * @description: STL 中 的变值算法 copy 函数示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template <class T>
class My_ostream_iterator : public iterator<output_iterator_tag, T> {
private:
    string sep;     // delimiter
    ostream &os;    // to store cout
public:
    My_ostream_iterator(ostream &o, string s) : sep(s), os(o) {}
    void operator++() {}
    My_ostream_iterator &operator*() {
        return *this;
    }
    My_ostream_iterator &operator=(const T &val) {
        os << val << sep;
        return *this;
    }
};

int main(int argc, char const *argv[]) {
    int a[4] = {1, 2, 3, 4};
    My_ostream_iterator<int> oit(cout, "*");
    copy(a, a + 4, oit);    // print 1*2*3*4
    ofstream oFile("test.txt", ios::out);
    My_ostream_iterator<int> oitf(oFile, "*");
    copy(a, a + 4, oitf);   // write 1*2*3*4 into test.txt
    oFile.close();
    return 0;
}
