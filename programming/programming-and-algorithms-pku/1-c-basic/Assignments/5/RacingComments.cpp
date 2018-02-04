/**
 * C语言中的运算成分 逻辑运算应用练习 抄写题 #1：点评赛车
 *
 * @file: RacingComments.cpp
 * @description: 4名专家对4款赛车进行评论
                    1）A说：2号赛车是最好的；
                    2）B说：4号赛车是最好的；
                    3）C说：3号赛车不是最好的；
                    4）D说： B说错了。
                事实上只有1款赛车最佳，且只有1名专家说对了，其他3人都说错了。请编程输出最佳车的车号，以及说对的专家。
 * @input: 无输入。
 * @output: 输出两行。第一行输出最佳车的车号（1-4中的某个数字）。第二行输出说对的专家（A-D中的某个字母）。
 * 样例输入
    (无)
 * 样例输出
    1
    A
 * @hint: 样例输出只是格式说明，并非正确答案。通过这道题我们想让大家知道如何通过枚举处理逻辑判断问题。
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // 用best枚举最好的车
    int best;
    for(best = 1; best <= 4; best++){
        // a b c d记录四位专家的话
        bool a = (best == 2);
        bool b = (best == 4);
        bool c = !(best == 3);
        bool d = !b;
        if (a + b + c + d != 1)
            continue; // 不符合只有1位专家说对的条件
        // 输出最佳的车
        cout << best << endl;
        // 输出判断正确的专家
        if ( a == 1)
            cout << "A" << endl;
        else if ( b == 1)
            cout << "B" << endl;
        else if ( c == 1)
            cout << "C" << endl;
        else
            cout << "D" << endl;
    }
    return 0;
}
