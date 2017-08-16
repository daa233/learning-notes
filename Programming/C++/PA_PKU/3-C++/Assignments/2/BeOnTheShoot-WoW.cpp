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
 * @date: Aug. 16th, 2017
 */

#include <iostream>
#include <iomanip>
#include <string>

class Warrior {
private:
    std::string name;
    int id;
    int strength;
    int attack;
    int count;
public:
    Warrior(std::string typeName, int s, int c) : name(typeName), strength(s), count(c) {}
    std::string getName() {
        return name;
    }
    int increaseWarriorCount() {
        return ++count;
    }
    int getWarriorStrength() {
        return strength;
    }
};

class Army {
private:
    std::string unit;   // red army for "red", blue army for "blue"
    int M;              // Army HP
    int totalWarriorCount;
    Warrior dragon;
    Warrior ninja;
    Warrior iceman;
    Warrior lion;
    Warrior wolf;
    std::string warriorMakingSequence[5];
    // int warriorStrengthSequence[5];
public:
    Army(std::string unitName, int hp, int ds, int ns, int is, int ls, int ws)
        : unit(unitName),
        M(hp),
        totalWarriorCount(0),
        dragon("dragon", ds, 0),
        ninja("ninja", ns, 0),
        iceman("iceman", is, 0),
        lion("lion", ls, 0),
        wolf("wolf", ws, 0)
    {
        if (unit == "red") {
            warriorMakingSequence[0] = iceman.getName();
            warriorMakingSequence[1] = lion.getName();
            warriorMakingSequence[2] = wolf.getName();
            warriorMakingSequence[3] = ninja.getName();
            warriorMakingSequence[4] = dragon.getName();
        } else if (unit == "blue") {
            warriorMakingSequence[0] = lion.getName();
            warriorMakingSequence[1] = dragon.getName();
            warriorMakingSequence[2] = ninja.getName();
            warriorMakingSequence[3] = iceman.getName();
            warriorMakingSequence[4] = wolf.getName();
        } else {
            exit(-1);
        }
    }
    int makeWarrior(int t, int index);
    int increaseWarriorCount(std::string name);
    int getWarriorStrengthByName(std::string name);
};

int Army::makeWarrior(int t, int index) {
    // judge the which kind warrior is going to make according to the army unit
    if (index == -1) {
        return -1;
    } else {
        for (int i = 0; i < 5; i++) {
            int cursor = (index + i) % 5;
            std::string warriorName = warriorMakingSequence[cursor];
            int strength = getWarriorStrengthByName(warriorName);
            int warriorCount = increaseWarriorCount(warriorName);
            if (M >= strength) {
                // std::cout << "M = "<< M << " strength = " << strength << std::endl;
                M = M - strength;
                std::cout << std::setfill('0') << std::setw(3);
                std::cout << t << " " << unit << " " <<  warriorName << " "
                << ++totalWarriorCount << " born with strength " << strength << ","
                << warriorCount << " " << warriorName << " in " << unit
                << " headquarter" << std::endl;
                return cursor + 1;
            } else {
                continue;
            }
        }
        std::cout << std::setfill('0') << std::setw(3);
        std::cout << t << " " << unit << " headquarter stops making warriors" << std::endl;
        return -1;  // can not make anymore
    }
}

int Army::increaseWarriorCount(std::string name){
    if (name == dragon.getName()) {
        return dragon.increaseWarriorCount();
    } else if (name == ninja.getName()) {
        return ninja.increaseWarriorCount();
    } else if (name == iceman.getName()) {
        return iceman.increaseWarriorCount();
    } else if (name == lion.getName()) {
        return lion.increaseWarriorCount();
    } else if (name == wolf.getName()) {
        return wolf.increaseWarriorCount();
    } else {
        exit(-1);
    }
}

int Army::getWarriorStrengthByName(std::string name) {
    if (name == dragon.getName()) {
        return dragon.getWarriorStrength();
    } else if (name == ninja.getName()) {
        return ninja.getWarriorStrength();
    } else if (name == iceman.getName()) {
        return iceman.getWarriorStrength();
    } else if (name == lion.getName()) {
        return lion.getWarriorStrength();
    } else if (name == wolf.getName()) {
        return wolf.getWarriorStrength();
    } else {
        exit(-1);
    }
}

int main(int argc, char const *argv[]) {
    // freopen("in.txt", "r", stdin);       // in.txt stores the sample input
    // freopen("outb.txt", "w", stdout);    // outb.txt stores the output of this program
    // And out.txt stores the sample out. Use diff out.txt outb.txt in terminal to compare.

    int caseNum;
    int M;
    int dragonStrength;
    int ninjaStrength;
    int icemanStrength;
    int lionStrength;
    int wolfStrength;

    std::cin >> caseNum;
    for (int i = 1; i <= caseNum; i++) {
        std::cin >> M;
        std::cin >> dragonStrength >> ninjaStrength >> icemanStrength >> lionStrength
                >> wolfStrength;
        std::cout << "Case:" << i << std::endl;

        Army redArmy("red", M, dragonStrength, ninjaStrength, icemanStrength, lionStrength,
                    wolfStrength);
        Army blueArmy("blue", M, dragonStrength, ninjaStrength, icemanStrength, lionStrength,
                    wolfStrength);
        int timeCount = 0;
        int redIndex = 0;
        int blueIndex = 0;
        while (true) {
            if (redIndex == -1 && blueIndex == -1) {
                break;
            } else {
                redIndex = redArmy.makeWarrior(timeCount, redIndex);
                blueIndex = blueArmy.makeWarrior(timeCount, blueIndex);
                timeCount++;
            }
        }
    }

    // fclose(stdin);
    // fclose(stdout);
    return 0;
}
