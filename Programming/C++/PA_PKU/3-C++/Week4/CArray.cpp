/**
 * 运算符重载实例：可变长整型数组
 *
 * @file: CArray.cpp
 * @description: 编写一个可变长的整型数组，需要多长就多长
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 20th, 2017
 */

#include <iostream>

class CArray {
private:
    int size;   // the number of the array elements
    int *ptr;   // pointer to the dynamic memory
public:
    CArray(int s = 0);  // constructor
    CArray(CArray &a);  // copy constructor
    ~CArray();  // destructor
    void push_back(int v);  // add one element in the end of the array
    CArray &operator=(const CArray &a); // assignment operator overloading
    int length() {return size;}
    // [] operator has two operands, support n = a[i]; a[i] = 4; like syntax
    int &operator[](int i) {return ptr[i];} // non-reference function return can not be lvalue
    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << ptr[i] << " ";
        }
        std::cout << std::endl;
    }
};

CArray::CArray(int s) : size(s) {   // constructor
    if (s == 0) {
        ptr = NULL;
    } else {
        ptr = new int[s];
    }
}

CArray::CArray(CArray &a) { // copy constructor
    if (!a.ptr) {
        ptr = NULL;
        size = 0;
        return;
    }
    size = a.size;
    ptr = new int[size];
    std::memcpy(ptr, a.ptr, sizeof(int) * size);
}

CArray::~CArray() { // destructor
    if (ptr) delete[] ptr;
}

CArray &CArray::operator=(const CArray &a) {    // assignment operator overloading
    if (ptr == a.ptr) { // self-assignment
        return *this;
    }
    if (a.ptr == NULL) {
        if (ptr) {
            delete[] ptr;
        }
        ptr = NULL;
        size = 0;
        return *this;
    }
    if (size < a.size) {    // if original memory is big enough, no need to allocate new memory
        if (ptr) {
            delete[] ptr;
        }
        ptr = new int[a.size];
    }
    std::memcpy(ptr, a.ptr, sizeof(int) * a.size);
    size = a.size;
    return *this;
}

void CArray::push_back(int v) { // add one element in the end of the array, ineffective
    if (ptr) {  // not empty
        int *tmpPtr = new int[size + 1];
        std::memcpy(tmpPtr, ptr, sizeof(int) * size);
        delete[] ptr;
        ptr = tmpPtr;
    } else { // empty
        ptr = new int[1];
    }
    ptr[size++] = v;    // add the new element
}

int main(int argc, char const *argv[]) {
    CArray a;
    for (int i = 0; i < 5; i++) {
        a.push_back(i); // dynamic allocate memory, need a pointer
    }
    CArray a2, a3;
    a2 = a; // overload assignment operator
    for (int i = 0; i < a.length(); ++i) {
        std::cout << a2[i] << " ";  // overload [] operator
    }
    a2 = a3;    // a2 is empty

    for (int i = 0; i < a2.length(); ++i) {  // a2.length() is 0
        std::cout << a2[i] << " ";
    }
    std::cout << std::endl;
    a[3] = 100;
    CArray a4(a);   // define copy constructor
    a4.print();

    return 0;
}
