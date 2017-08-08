/**
 * 综合编程练习（2） 编程题＃1：分配病房
 *
 * @file: AllocateWards.cpp
 * @description: 某个科室的病房分为重症和普通，只有当病人的疾病严重程度超过了入住重症病房的最低严重值，才可以安排入
                住重症病房。现在要求设计一个程序，给病人安排好病房。疾病的严重程度用 0 到 10 来表示，0 表示小毛病，
                10 表示非常严重。
 * @input: 第一行输入病人的个数 m(m < 50)，以及安排住入重症病房的最低严重值 a，紧接着 m 行，每行表示病人编号（三个
        位，用 0 补齐）及其疾病的严重程度（浮点数，1 位小数）。每个病人的疾病严重程度都不一样。
 * @output: 要求按照病人的严重程度输出住在重症病房里的病人的编号
        注意：如果当前所有病人的严重程度并不满足住在重症病房里，则输出“None.”（不包括引号）
 * @sample_input:
    10 7.55
    006 6.5
    005 8.0
    004 3.5
    009 8.5
    011 7.0
    043 9.5
    003 5.0
    103 6.0
    112 4.0
    118 9.0
 * @sample_output:
    043 9.5
    118 9.0
    009 8.5
    005 8.0
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

// primeArray[] and slaveArray have same length, size down
void sortBindArray(float primeArray[], int slaveArray[], int length)
{
    for (int i = 0; i < length-1; i++) {
        for (int j = 0; j < length-1-i; j++) {
            if (primeArray[j] < primeArray[j+1]) {
                float tempInt = primeArray[j];
                int tempFloat = slaveArray[j];
                primeArray[j] = primeArray[j+1];
                slaveArray[j] = slaveArray[j+1];
                primeArray[j+1] = tempInt;
                slaveArray[j+1] = tempFloat;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    int m = 0;
    float limit = 0.0;
    cin >> m >> limit;   // m is less than 50
    int num[m];
    float level[m];
    int icuNum[m];      // for the patients who can be allocated
    float icuLevel[m];
    int count = 0;      // count for patients who can be allocated

    for (int i = 0; i < m; i++) {
        cin >> num[i] >> level[i];
        if (level[i] > limit) {
            icuNum[count] = num[i];
            icuLevel[count] = level[i];
            count++;
        }
    }
    if (count <= 0) {
        cout << "None." << endl;
    } else {
        sortBindArray(icuLevel, icuNum, count);
        for (int i = 0; i < count; i++) {
            cout << setw(3) << setfill('0');
            cout << icuNum[i] << " ";
            cout << fixed;
            cout << setprecision(1) << icuLevel[i] << endl;
        }
    }

    return 0;
}
