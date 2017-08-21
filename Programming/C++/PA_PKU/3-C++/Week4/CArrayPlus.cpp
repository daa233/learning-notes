/**
 * 运算符重载实例：可变长整型数组（加强版）
 *
 * @file: CArrayPlus.cpp
 * @description: 编写一个可变长的整型数组，需要多长就多长，并且希望 push_back() 函数更加高效。方法是申请内存时
                不要每次只申请一个，可以多申请一些，获得冗余的存储空间。
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 21st, 2017
 */

#include <iostream>
#include <time.h>

class CArrayPlus {
private:
    int size;           // the number of the array elements
    int *ptr;           // pointer to the dynamic memory
    int memorySize;     // real memory size
    static const int unitMemorySize = 32;   // the minimum memory size of the array
public:
    CArrayPlus(int s = 0);      // constructor
    CArrayPlus(CArrayPlus &a);  // copy constructor
    ~CArrayPlus();              // destructor
    void push_back(int v);      // add one element in the end of array
    CArrayPlus &operator=(const CArrayPlus &a); // assignment operator overloading
    int length() {return size;}                 // return the length(size) of the array
    int &operator[](int i) {return ptr[i];}     // [] operator overloading
    void print() {      // print the array
        for (int i = 0; i < size; ++i) {
            std::cout << ptr[i] << " ";
        }
        std::cout << std::endl;
    }
};

// constructor
CArrayPlus::CArrayPlus(int s) : size(s) {
    if (s == 0) {
        ptr = NULL;
    } else {
        // 1. memorySize = 2 ^ n;
        // 2. memorySize >= max(size, unitMemorySize);
        int i = unitMemorySize;
        while (true) {
            if (s <= i) {
                memorySize = i;
                break;
            } else {
                i = i * 2;
            }
        }
        ptr = new int[memorySize];
    }
}

// copy constructor
CArrayPlus::CArrayPlus(CArrayPlus &a) {
    if (!a.ptr) {
        ptr = NULL;
        size = 0;
        return;
    }
    ptr = new int[a.memorySize];
    std::memcpy(ptr, a.ptr, sizeof(int) * a.memorySize);
    size = a.size;
    memorySize = a.memorySize;
}

// destructor
CArrayPlus::~CArrayPlus() {
    if (ptr) delete[] ptr;
}

// assignment operator overloading
CArrayPlus &CArrayPlus::operator=(const CArrayPlus &a) {
    if (ptr == a.ptr) {
        return *this;
    }
    if (a.ptr == NULL) {
        if (ptr) {
            delete[] ptr;
        }
        ptr = NULL;
        size = 0;
        memorySize = 0;
        return *this;
    }
    if (size < a.size) {
        if (ptr) {
            delete[] ptr;
        }
        ptr = new int[a.memorySize];
    }
    std::memcpy(ptr, a.ptr, sizeof(int) * a.memorySize);
    size = a.size;
    memorySize = a.memorySize;
    return *this;
}

// add one element in the end of the array, a more effective version
void CArrayPlus::push_back(int v) {
    if (ptr) {  // the array is not empty
        if (size + 1 > memorySize) {
            int i = memorySize;
            while (true) {
                if (size + 1 <= i) {
                    memorySize = i;
                    break;
                } else {
                    i = i * 2;
                }
            }
            int *tmpPtr = new int[memorySize];
            std::memcpy(tmpPtr, ptr, sizeof(int) * size);
            delete[] ptr;
            ptr = tmpPtr;
        }
    } else {    // the array is empty
        ptr = new int[unitMemorySize];
        memorySize = unitMemorySize;
    }
    ptr[size++] = v;    // add the new element
}


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
    int n = 200000;
    std::cout << "Compare CArrayPlus and CArray's efficiency by push_back " << n << " numbers"
            << std::endl;
    // Compare CArrayPlus and CArray's efficiency by push_back 200000 numbers
    clock_t begin = clock();
    CArrayPlus a;
    for (int i = 0; i < n; i++) {
        a.push_back(i);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "CArrayPlus time cost: " << time_spent << " s" << std::endl;
    // CArrayPlus time cost: 0.001743 s

    begin = clock();
    CArray b;
    for (int i = 0; i < n; i++) {
        b.push_back(i);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "CArray time cost: " << time_spent << " s" << std::endl;
    // CArray time cost: 3.87979 s
    return 0;
}
