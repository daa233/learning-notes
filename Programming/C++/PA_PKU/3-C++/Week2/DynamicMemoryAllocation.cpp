/**
 * @file: DynamicMemoryAllocation.cpp
 * @description: 动态内存分配
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    // 动态分配变量
    int *pn;
    pn = new int;
    *pn = 5;
    delete pn;
    // 重复 delete 会导致运行时异常
    // alloc: *** error for object 0x7fa74b4026a0: pointer being freed was not allocated
    // delete pn;

    // 动态分配数组
    int i =5;
    pn = new int[i * 20];
    pn[0] = 20;
    // pn[100] = 30;   // 编译没错，运行时有可能导致数组越界报错。gcc/g++ 不检查数组越界。
    delete[] pn;

    return 0;
}
