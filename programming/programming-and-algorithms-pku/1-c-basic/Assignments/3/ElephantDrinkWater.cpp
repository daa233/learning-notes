/**
 * 理性认识C程序  编程题 #2：大象喝水
 *
 * @file: ElephantDrinkWater.cpp
 * @description: 一只大象口渴了，要喝20升水才能解渴，但现在只有一个深h厘米，底面半径为r厘米的小圆桶(h和r都是整数)。问大象至少要喝
                多少桶水才会解渴。
 * @input: 输入有一行：包行两个整数，以一个空格分开，分别表示小圆桶的深h和底面半径r，单位都是厘米。
 * @output: 输出一行，包含一个整数，表示大象至少要喝水的桶数。
 * 样例输入
    第一组
    23 11
    第二组
    1 1
 * 样例输出
    第一组
    3
    第二组
    6367
 * 提示：如果一个圆桶的深为h厘米，底面半径为r厘米，那么它最多能装Pi * r * r * h立方厘米的水。(设Pi=3.14159)
        1升 = 1000毫升 1毫升 = 1 立方厘米
 *
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

#include <iostream>
#include <math.h>   // 为了使用ceil()函数

using namespace std;

int main(int argc, char *argv[])
{
    float const PI = 3.14159;   // 圆周率常量PI
    int const NEED_WATER = 20 * 1000;    // 大象需要喝的水，20升，转化为平方厘米
    int h, r;   // 小圆桶的深h，底面半径r
    float v;    // 小圆桶的体积
    int n;      // 大象需要喝的桶数

    cin >> h >> r;
    v = PI * h * r * r;
    n = ceil(NEED_WATER / v);   // ceil(a)函数返回大于a的最小整数
    cout << n << endl;
    return 0;
}
