/**
 *  文件操作和模板 编程题＃1
 *
 * @file: Week7Ex1.cpp
 * @description: 程序填空
            实现一个三维数组模版 CArray3D，可以用来生成元素为任意类型变量的三维数组，使得下面程序输出结果是：
            0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,（无换行）
            29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,（无换行）
            55,56,57,58,59,
            注意：只能写一个类模版，不能写多个。
 * @sample_input:
    none
 * @sample_output:
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,（无换行）
    32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
 * @hint: 类里面可以定义类，类模版里面也可以定义类模版。例如：
    class A
    {
        class B {

        };
    };

    template
    class S
    {
        T x;
        class K {
            T a;
        };
    };
 *
 * @author: Du Ang
 * @date: Aug. 26th, 2017
 */

#include <iostream>
using namespace std;

// 在此处补充你的代码
template <class T>
class CArray3D {
private:
    T ***p;
public:
    CArray3D(T h, T w, T l) {
        p = new T**[h];
        for (int i = 0; i < h; i++) {
            p[i] = new T*[w];
            for (int j = 0; j < w; j++) {
                p[i][j] = new T[l];
            }
        }
    }

    class Proxy2D {
    private:
        T **p;
    public:
        class Proxy1D {
        private:
            T *p;
        public:
            Proxy1D(T *ptr) : p(ptr) {}
            T &operator[](int i) {
                return p[i];
            }
        };

        Proxy2D(T **ptr) : p(ptr) {}

        Proxy1D operator[](int i) {
            return Proxy1D(p[i]);
        }

    };

    Proxy2D operator[](int i) {
        return Proxy2D(p[i]);
    }
};

int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
    return 0;
}
