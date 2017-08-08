/**
 * @file: ArrayNameAsFuncParams.cpp
 * @description: 数组名做函数参数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>

using namespace std;

void sum(int *p, int n)
{
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += *p++;
    }
    cout << total << endl;
}

int sumArray(int array[], int n)
{
    for (int i = 0; i < 10 - 1; i++) {
        *(array + 1) = *array + *(array + 1);
        array++;
    }
    return *array;
}

int maxValue(int (*p)[4])
{
    int max = p[0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (p[i][j] > max) {
                max = p[i][j];
            }
        }
    }
    return max;
}

int main(int argc, char const *argv[]) {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[3][4] = {{1, 3, 5, 7}, {9, 11, 13, 15}, {2, 4, 6, 8}};

    sum(a, 10);
    cout << "The max value is " << maxValue(b) << endl;
    cout << sumArray(a, 10) << endl;
    return 0;
}
