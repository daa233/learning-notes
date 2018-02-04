/**
 * C语言中的数据成分 综合练习（1）编程题 #1：年龄与疾病
 *
 * @file: AgeAndDiseases.cpp
 * @description: 某医院想统计一下某项疾病的获得与否与年龄是否有关，需要对以前的诊断记录进行整理。
 * @input: 共2行，第一行为过往病人的数目n（0 < n <= 100)，第二行为每个病人患病时的年龄。
 * @output: 每个年龄段（分四段：18以下，19-35，36-60，大于60。注意看样例输出的格式）的患病人数占总患病人数的比例，以百分比的形式输
            出，精确到小数点后两位（double）。
            关于c++的格式化的输入输出，请参考：http://www.cplusplus.com/reference/iomanip。
 * 样例输入
    10
    1 11 21 31 41 51 61 71 81 91
 * 样例输出
    1-18: 20.00%
    19-35: 20.00%
    36-60: 20.00%
    60-: 40.00%
 * @hint: 注意最后一行的输出是“60-: ”，而不是“61-: ”。每个冒号之后有一个空格。
        输出可以用 cout<<fixed<<setprecision(2) << f; 来保留f后面的两位小数。
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    int n;          // 病人的数目
    int age[100];   // 病人患病时的年龄
    // 四个年龄段的人数
    int firstAgeNum = 0, secondAgeNum = 0, thirdAgeNum = 0, forthAgeNum = 0;
    // 四个年龄段占总人数的比例
    float firstAgePercent = 0, secondAgePercent = 0;
    float thirdAgePercent = 0, forthAgePercent = 0;

    cin >> n;       // 输入病人的数目
    for (int i = 0; i < n; i++) {
        cin >> age[i];  // 输入病人的年龄
        if (age[i] <= 18) {
            firstAgeNum++;
        } else if (age[i] <= 35) {
            secondAgeNum++;
        } else if (age[i] <= 60) {
            thirdAgeNum++;
        } else {
            forthAgeNum++;
        }
    }
    // 计算各年龄段人数占总人数的百分比
    firstAgePercent = (float) firstAgeNum / n * 100;
    secondAgePercent = (float) secondAgeNum / n * 100;
    thirdAgePercent = (float) thirdAgeNum / n * 100;
    forthAgePercent = (float) forthAgeNum / n * 100;
    cout << fixed << setprecision(2);   // 设置输出格式小数点固定，精度为两位
    cout << "1-18: " << firstAgePercent << "%" << endl;
    cout << "19-35: " << secondAgePercent << "%" << endl;
    cout << "36-60: " << thirdAgePercent << "%" << endl;
    cout << "60-: " << forthAgePercent << "%" << endl;

    return 0;
}
