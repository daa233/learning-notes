/**
 *  运算符重载 编程题＃3
 *
 * @file: Week4Ex2.cpp
 * @description: 程序填空
                写一个二维数组类 Array2,使得下面程序的输出结果是：
                0,1,2,3,
                4,5,6,7,
                8,9,10,11,
                next
                0,1,2,3,
                4,5,6,7,
                8,9,10,11,
 * @sample_input:
    none
 * @sample_output:
    0,1,2,3,
    4,5,6,7,
    8,9,10,11,
    next
    0,1,2,3,
    4,5,6,7,
    8,9,10,11,
 *
 * @author: Du Ang
 * @date: Aug. 21st, 2017
 */

#include <iostream>
#include <cstring>

using namespace std;

class Array2 {
// 在此处补充你的代码
private:
    int **p;
public:
    Array2() {
        p = NULL;
    }
    Array2(int m, int n) {
        p = new int*[m];
        for (int i = 0; i < m; i++) {
            p[i] = new int[n];
        }
    }
    int &operator()(int row, int col) { // overload parenthesis operator
        return p[row][col];
    }

    // refer to https://stackoverflow.com/questions/6969881/operator-overload
    class RowVector {
    private:
        int *p;
    public:
        RowVector(int *ptr) : p(ptr) {}
        int &operator[](int n) {
            return p[n];
        }
    };

    RowVector operator[](int n) {   // operator [] overloading
        return RowVector(p[n]);
    }
};

int main() {
    Array2 a(3,4);
    int i, j;
    for(i = 0; i < 3; ++i)
        for(j = 0; j < 4; j++ )
            a[i][j] = i * 4 + j;
    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 4; j++) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;
    b = a;
    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 4; j++) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
