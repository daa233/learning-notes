/**
 * @file: PointerToSymbolicConstants.cpp
 * @description: 指向符号常量的指针
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>

using namespace std;

int sum(const int array[], int n)
{
    for (int i = 0; i < 10 - 1; i++) {
        // *(array + 1) = *array + *(array + 1);    // error: read-only variable is not assignable
        array++;
    }
    return *array;
}

int main(int argc, char const *argv[]) {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << sum(a, 10);

    int b = 256;
    const int *p = &b;
    // *p = 257;            // error: read-only variable is not assignable
    cout << *p << endl;

    const int c = 78;
    const int d = 28;
    int e = 18;
    const int *pi = &c;
    // *pi = 58;                // error: read-only variable is not assignable
    pi = &d;                    // pi can be re-assigned value, now pi points to d
    // *pi = 68;                // error: read-only variable is not assignable
    pi = &e;                    // now pi points to e
    // *pi = 88;                // error: read-only variable is not assignable

    return 0;
}
