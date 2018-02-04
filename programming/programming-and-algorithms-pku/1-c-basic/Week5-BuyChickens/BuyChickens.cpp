/**
 * @file: BuyChickens.cpp
 * @description: 百元买百鸡问题。假定小鸡每只5角，公鸡每只两元，母鸡每只3元。100元买100只鸡，列出所有够鸡方案。
 * @solution: 设母鸡、公鸡、小鸡数量分别为x, y, z，
 *          列出三元一次方程，x + y + z = 100, 3x + 2y + 0.5z = 100。联立化简后为 5x + 3y = 100
 *          遍历x, y，找出所有可能结果。注意x, y, z的取值范围。
 *
 *
 * @author: Du Ang
 * @date: Apr. 3rd, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "母鸡" << "\t\t" << "公鸡" << "\t\t" << "小鸡" << endl;
    for (int x = 0; x <= 20; x++) {
        for (int y = 0; y <= 33; y++) {
            if ((5*x + 3*y) == 100) {
                cout << x << "\t\t" << y << "\t\t" << 100-x-y << endl;
            }
        }
    }
    return 0;
}
