/**
 * 类与对象 编程题＃4：魔兽世界之一：备战
 *
 * @file: BeOnTheShoot-WoW.cpp
 * @description: 魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。
                红司令部，City 1，City 2，……，City n，蓝司令部

                两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编
                号、生命值、攻击力这三种属性。双方的武士编号都是从 1 开始计算。红方制造出来的第 n 个武士，编号就
                是 n。
                同样，蓝方制造出来的第 n 个武士，编号也是 n。武士在刚降生的时候有一个生命值。 在每个整点，双方的司
                令部中各有一个武士降生。

                红方司令部按照 iceman、lion、wolf、ninja、dragon的顺序循环制造武士。蓝方司令部按照 lion、
                dragon、ninja、iceman、wolf的顺序循环制造武士。

                制造武士需要生命元。制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。如果司令部中的生
                命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司
                令部停止制造武士。

                给定一个时间，和双方司令部的初始生命元数目，要求你将从 0 点 0 分开始到双方司令部停止制造武士为止的
                所有事件按顺序输出。

                一共有两种事件，其对应的输出样例如下：
                1) 武士降生
                输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
                表示在 4 点整，编号为 5 的蓝魔 lion 武士降生，它降生时生命值为 5，降生后蓝魔司令部里共有 2 个
                lion 武士。（为简单起见，不考虑单词的复数形式）注意，每制造出一个新的武士，都要输出此时司令部里共有
                多少个该种武士。
                2) 司令部停止制造武士
                输出样例： 010 red headquarter stops making warriors
                表示在 10 点整，红方司令部停止制造武士
                输出事件时：
                首先按时间顺序输出；同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。
 * @input: 第一行是一个整数，代表测试数据组数。每组测试数据共两行。
        第一行：一个整数M。其含义为， 每个司令部一开始都有M个生命元( 1 <= M <= 10000)。
        第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于 0 小于等于 10000。
 * @output: 对每组测试数据，要求输出从 0 时 0 分开始，到双方司令部都停止制造武士为止的所有事件。
        对每组测试数据，首先输出 "Case:n"  n 是测试数据的编号，从 1 开始 。
        接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。
 * @sample_input:
    1
    20
    3 4 5 6 7
 * @sample_output:
    Case:1
    000 red iceman 1 born with strength 5,1 iceman in red headquarter
    000 blue lion 1 born with strength 6,1 lion in blue headquarter
    001 red lion 2 born with strength 6,1 lion in red headquarter
    001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
    002 red wolf 3 born with strength 7,1 wolf in red headquarter
    002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
    003 red headquarter stops making warriors
    003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
    004 blue headquarter stops making warriors
 *
 * @author: Du Ang
 * @date: Aug. 15th, 2017
 */

#include <iostream>

int main(int argc, char const *argv[]) {

    return 0;
}
