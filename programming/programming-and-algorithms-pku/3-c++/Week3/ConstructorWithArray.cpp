/**
 * @file: ConstructorWithArray.cpp
 * @description: 构造函数在数组中的使用
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 13th, 2017
 */

#include <iostream>

using namespace std;

class CSample {
private:
    int x;
public:
    CSample() {
        cout << "CSample constructor 1 is called." << endl;
    }
    CSample(int n) {
        x = n;
        cout << "CSample constructor 2 is called." << endl;
    }
};

class Test {
public:
    Test(int n) {
        cout << "Test constructor 1 is called." << endl;
    }
    Test(int n, int m) {
        cout << "Test constructor 2 is called." << endl;
    }
    Test() {
        cout << "Test constructor 3 is called." << endl;
    }
};

int main(int argc, char const *argv[]) {
    CSample array1[2];  // 对象数组
    // CSample constructor 1 is called.
    // CSample constructor 1 is called.
    cout << "step 1" << endl;
    CSample array2[2] = {4, 5}; // 等同于 CSample array2[2] = {CSample(4), CSample(5)};
    // CSample constructor 2 is called.
    // CSample constructor 2 is called.
    cout << "step 2" << endl;
    CSample array3[2] = {3};
    // CSample constructor 2 is called.
    // CSample constructor 1 is called.
    cout << "step 3" << endl;
    CSample *array4 = new CSample[2];
    // CSample constructor 1 is called.
    // CSample constructor 1 is called;
    delete[] array4;

    Test testArray1[3] = {1, Test(1, 2)};
    // Test constructor 1 is called
    // Test constructor 2 is called
    // Test constructor 3 is called
    Test testArray2[3] = {Test(2, 3), Test(1, 2), 1};
    // Test constructor 2 is called
    // Test constructor 2 is called
    // Test constructor 1 is called
    Test *pArray[3] = {new Test(4), new Test(1, 2)}; // pArray[3] 是指针数组，不是对象数组
    // Test constructor 1 is called
    // Test constructor 2 is called
    // pArray[2] 是一个未初始化的指针
    return 0;
}
