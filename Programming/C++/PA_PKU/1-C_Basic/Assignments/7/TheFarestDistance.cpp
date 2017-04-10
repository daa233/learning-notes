/**
 * 期末编程测试 编程题 #3：最远距离
 *
 * @file: TheFarestDistance.cpp
 * @description: 给定一组点(x,y)，求距离最远的两个点之间的距离。
 * @input: 第一行是点数n（n大于等于2），接着每一行代表一个点，由两个浮点数x y组成。
 * @output: 输出一行是最远两点之间的距离。使用cout << fixed << setprecision(4) << dis << endl;
            输出距离值并精确到小数点后4位。fixed和setprecision是在<iomanip>头文件里定义的格式控制操作符，需要
            #include <iomanip>.
 * 样例输入
    6
    34.0 23.0
    28.1 21.6
    14.7 17.1
    17.0 27.2
    34.7 67.1
    29.3 65.1
 * 样例输出
    53.8516
 * @hint: 注意在内部计算时最好使用double类型，但在用scanf读取数据时只能用float类型的变量。
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
    /* 求距离最远的两个点，可以先找四个特殊点——即x、y坐标分别是最大、最小的点。可以证明，最远的点的距离一定是这四个点的对角线之一（不重合时的
    情况）。如果四个点有重合的情况，也可以当作没有重合来处理，把它们作为四个独立的点来计算，重合点之间的距离为0。 */
    int n; // 点数
    cin >> n;
    double p[n][2] = {0};  // 点坐标数组
    int xMinIndex = 0, xMaxIndex = 0, yMinIndex = 0, yMaxIndex = 0;// 记录特殊点的位置
    double xMin, xMax, yMin, yMax;     // 记录特殊点的值
    double farestDistance = 0;  // 最远距离
    for (int i = 0; i < n; i++) {
        cin >> p[i][0];
        cin >> p[i][1];
        double tempX = p[i][0];
        double tempY = p[i][1];
        if (i == 0) {
            xMin = xMax = tempX;   // 初始化特殊点全部为第一个输入的点
            yMin = yMax = tempY;
        } else {   // 更新特殊点的值和位置
            if (tempX > xMax) {
                xMax = tempX;
                xMaxIndex = i;
            }
            if (tempX < xMin) {
                xMin = tempX;
                xMinIndex = i;
            }
            if (tempY > yMax) {
                yMax = tempY;
                yMaxIndex = i;
            }
            if (tempY < yMin) {
                yMin = tempY;
                yMinIndex = i;
            }
        }
    }

    double dp1 = 0, dp2 = 0;  // 记录四个点组成的四边形对角线长度的平方
    dp1 = pow((p[xMaxIndex][0] - p[xMinIndex][0]), 2)
            + pow((p[xMaxIndex][1] - p[xMinIndex][1]), 2);
    dp2 = pow((p[yMaxIndex][0] - p[yMinIndex][0]), 2)
            + pow((p[yMaxIndex][1] - p[yMinIndex][1]), 2);
    farestDistance = dp1 > dp2 ? sqrt(dp1) : sqrt(dp2); // 最远距离为d1、d2中较大的那一个的开方
    cout << fixed << setprecision(4) << farestDistance << endl;

    return 0;
}
