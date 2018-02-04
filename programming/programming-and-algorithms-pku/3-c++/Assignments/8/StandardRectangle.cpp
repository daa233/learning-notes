/**
 *  标准模板库 STL-2 编程题＃1
 *
 * @file: StandardRectangle.cpp
 * @description: 程序填空
                下面的程序用枚举法解决如下问题，请填空。
                平面上的一个矩形，如果其边平行于坐标轴，我们就称其为“标准矩形”。给定不重复的 n 个整点（横、纵坐标都
                是整数的点），求从这 n 个点中任取 4 点作为顶点所构成的四边形中，有多少个是标准矩形。
 * @input: 第一行是点的数目，其后每一行都代表一个点，由两个整数表示，第一个是 x 坐标，第二个是 y 坐标
 * @output: 输出标准矩形的数目
 * @sample_input:
    6
    2 3
    2 5
    4 5
    4 4
    2 4
    4 3
 * @sample_output:
    3
 * @hint: 所缺代码具有如下形式：
     _____________________;
    for( i = v.begin(); i < v.end() - 1;i ++ )
        for(_____________; ______________; _____________) {
            if(binary_search(v.begin(),v.end(),Point( j->x, i->y))  &&
                ____________________________________________ &&
                ____________________________________________ &&
                ____________________________________________ )
                nTotalNum ++;
        }
    cout << _________________;
 *
 * @author: Du Ang
 * @date: Aug. 31st, 2017
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x;
    int y;
    Point(int x_,int y_):x(x_),y(y_) { }
};

bool operator<(const Point & p1, const Point & p2)
{
    if( p1.y < p2.y )
        return true;
    else if( p1.y == p2.y )
        return p1.x < p2.x;
    else
        return false;
}

int main()
{
    int t;
    int x,y;
    cin >> t;
    vector<Point> v;
    while ( t -- ) {
        cin >> x >> y;
        v.push_back(Point(x,y));
    }
    vector<Point>::iterator i, j;
    int nTotalNum = 0;
    // 在此处补充你的代码
    sort(v.begin(), v.end());
    for (i = v.begin(); i < v.end(); i++) {
        for (j = v.begin(); j < v.end(); j++) {
            if (binary_search(v.begin(), v.end(), Point(j->x, i->y))
                && binary_search(v.begin(), v.end(), Point(i->x, j->y))
                && (i->x != j->x) && (i->y != j->y)) {
                nTotalNum++;
            }
        }
    }
    cout << nTotalNum / 4 << endl;
    return 0;
}
