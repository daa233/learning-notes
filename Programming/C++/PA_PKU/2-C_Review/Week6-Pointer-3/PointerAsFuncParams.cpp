/**
 * @file: PointerAsFuncParams.cpp
 * @description: 指针做函数参数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>

using namespace std;

void Rank(int *q1, int *q2)
{
    int temp;
    if (*q1 < *q2) {
        temp = *q1;
        *q1 = *q2;
        *q2 = temp;
    }
}

int main(int argc, char const *argv[]) {
    int a, b, *p1, *p2;
    cin >> a >> b;
    p1 = &a;
    p2 = &b;
    Rank(p1, p2);
    cout << a << " " << b << endl;
    return 0;
}
