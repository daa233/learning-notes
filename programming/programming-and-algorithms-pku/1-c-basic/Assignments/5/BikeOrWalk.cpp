/**
 * C语言中的运算成分 逻辑运算应用练习 综合练习（2）#2：骑车与走路
 *
 * @file: BikeOrWalk.cpp
 * @description: 在北大校园里,没有自行车,上课办事会很不方便.但实际上,并非去办任何事情都是骑车快,因为骑车总要找车、开锁、停车、锁车
                等,这要耽误一些时间.假设找到自行车,开锁并车上自行车的时间为27秒;停车锁车的时间为23秒;步行每秒行走1.2米,骑车每秒
                行走3.0米.请判断走不同的距离去办事,是骑车快还是走路快.
 * @input: 第一行为待处理的数据的数量n，其后每一行整数为一次办事要行走的距离,单位为米.
 * @output: 对应每个整数,如果骑车快,输出一行"Bike";如果走路快,输出一行"Walk";如果一样快,输出一行"All"
 * @hint: 注意数据类型，应当使用浮点数来保存结果
 * 样例输入
    4
    50
    90
    120
    180
 * 样例输出
    Walk
    Walk
    Bike
    Bike
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;          // 数据组数
    cin >> n;       // 输入数据组数
    double d[n];    // 每组的距离
    double bikeTime = 0;   // 骑车要花的总时间
    double walkTime = 0;   // 走路要花的总时间
    double a = 2.0; double b = 2.0;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        bikeTime = d[i] / 3 + 27 +23;   // 骑车总时间
        walkTime = d[i] / 1.2;          // 走路总时间
        if (bikeTime < walkTime) {
            cout << "Bike" << endl;     // 骑车时间短
        } else if (bikeTime > walkTime) {
            cout << "Walk" << endl;     // 时间一样长
        } else {    // 注意：这里最好不要用 == 比较两个浮点数
            cout << "All" << endl;      // 走路时间短
        }
    }
    return 0;
}
