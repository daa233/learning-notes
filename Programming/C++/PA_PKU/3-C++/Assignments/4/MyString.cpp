/**
  *  继承与派生 编程题＃1：程序填空题（注：OpenJudge 上的此题目存在问题，不应该使用 qsort 排序）
  *
  * @file: MyString.cpp
  * @description: 写一个 MyString 类，使得下面程序的输出结果是：
                1. abcd-efgh-abcd-
                2. abcd-
                3.
                4. abcd-efgh-
                5. efgh-
                6. c
                7. abcd-
                8. ijAl-
                9. ijAl-mnop
                10. qrst-abcd-
                11. abcd-qrst-abcd- uvw xyz
                about
                big
                me
                take
                abcd
                qrst-abcd-

            要求：MyString 类必须是从 C++ 的标准类 string 类派生而来。
            提示1：如果将程序中所有“MyString”用“string”替换，那么题目的程序中除了最后两条语句编译无法通过外，其
            他语句都没有问题，而且输出和前面给的结果吻合。也就是说，MyString 类对 string 类的功能扩充只体现在最后
            两条语句上面。
            提示2：string 类有一个成员函数 string substr(int start,int length); 能够求从 start 位置开始，
            长度为 length的子串
 * @sample_input:
    none
 * @sample_output:
    1. abcd-efgh-abcd-
    2. abcd-
    3.
    4. abcd-efgh-
    5. efgh-
    6. c
    7. abcd-
    8. ijAl-
    9. ijAl-mnop
    10. qrst-abcd-
    11. abcd-qrst-abcd- uvw xyz
    about
    big
    me
    take
    abcd
    qrst-abcd-
 *
 * @author: Du Ang
 * @date: Aug. 23rd, 2017
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

/******************************************************/
// 在此处补充你的代码
class MyString : public string {
public:
    MyString();
    MyString(const string &s);
    MyString(const char *s);
    MyString operator()(int start, int length);
};

MyString::MyString() : string() {}

MyString::MyString(const string &s) : string(s) {}

MyString::MyString(const char *s) : string(s) {}

MyString MyString::operator()(int start, int length) {
    return this->substr(start, length);
}

/******************************************************/

int CompareString( const void * e1, const void * e2) {
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
    if( *s1 < *s2 )     return -1;
    else if( *s1 == *s2 ) return 0;
    else if( *s1 > *s2 ) return 1;
    else exit(-1);
}

int main() {
    MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
    MyString SArray[4] = {"big", "me", "about", "take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;

    // error in using qsort, use sort instead.
    // https://stackoverflow.com/questions/12459290/how-to-compare-c-string-using-qsort-in-c
    // https://stackoverflow.com/questions/41076108/no-viable-constructor-copying-array-element-of-type-mystring
    // qsort(SArray, 4, sizeof(MyString), CompareString);
    sort(SArray, SArray + 4);

    for( int i = 0; i < 4; ++i )
        cout << SArray[i] << endl;
    //输出s1从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //输出s1从下标为5开始长度为10的子串
    cout << s1(5,10) << endl;
    return 0;
}
