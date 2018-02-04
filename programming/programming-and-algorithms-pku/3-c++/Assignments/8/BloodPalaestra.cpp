/**
 *  标准模板库 STL-2 编程题＃5 热血格斗场
 *
 * @file: BloodPalaestra.cpp
 * @description: 为了迎接 08 年的奥运会，让大家更加了解各种格斗运动，Facer 新开了一家热血格斗场。格斗场实行会员制，
                但是新来的会员不需要交入会费，而只要同一名老会员打一场表演赛，证明自己的实力。

                我们假设格斗的实力可以用一个正整数表示，成为实力值。另外，每个人都有一个唯一的 id，也是一个正整数。
                为了使得比赛更好看，每一个新队员都会选择与他实力最为接近的人比赛，即比赛双方的实力值之差的绝对值越小
                越好，如果有两个人的实力值与他差别相同，则他会选择比他弱的那个（显然，虐人比被虐好）。

                不幸的是，Facer 一不小心把比赛记录弄丢了，但是他还保留着会员的注册记录。现在请你帮 Facer 恢复比赛
                纪录，按照时间顺序依次输出每场比赛双方的 id。


 * @input: 第一行一个数 n(0 < n <= 100000)，表示格斗场新来的会员数（不包括 Facer）。以后 n 行每一行两个数，按照
        入会的时间给出会员的 id 和实力值。一开始，Facer就算是会员，id 为 1，实力值 1000000000。输入保证两人的实力
        值不同。
 * @output: N 行，每行两个数，为每场比赛双方的 id，新手的 id 写在前面。
 * @sample_input:
    3
    2 1
    3 3
    4 2
 * @sample_output:
    2 1
    3 2
    4 2
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {
    multimap<int, int> members;
    members.insert(make_pair(1000000000, 1));
    int n;  // the number of new members
    cin >> n;
    while (n--) {
        int id, strength;
        cin >> id >> strength;
        int rivalId;
        multimap<int, int>::iterator i = members.insert(make_pair(strength, id));
        multimap<int, int>::iterator j = i;
        // multimap will sort the elements automatically when insert them
        // just look at the neighbor of the new inserted element
        if (i == members.begin()) {
            rivalId = (++i)->second;
        } else if ((++j) == members.end()) {
            --(--j);
            rivalId = j->second;
        } else {
            ++i;
            --(--j);
            if ((i->first - strength) >= (strength - j->first)) {
                rivalId = j->second;
            } else {
                rivalId = i->second;
            }
        }
        cout << id << " " << rivalId << endl;
    }
    return 0;
}
