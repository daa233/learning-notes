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
#include <vector>
#include <iomanip>

using namespace std;

string getWeaponName(int i);
vector<string> getWarriorsProduceSequence(string color);

/**
  *  继承与派生 编程题＃2：魔兽世界之二：装备
  *
  * @file: Equipment-WoW.cpp
  * @description: 魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。
                 红司令部，City 1，City 2，……，City n，蓝司令部

                 两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编
                 号、生命值这两种属性。 有的武士可以拥有武器。武器有三种，sword, bomb,和 arrow，编号分别为 0,
                 1, 2。

                 双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个
                 武士，编号也是n。 双方的武士编号都是从 1 开始计算。红方制造出来的第 n 个武士，编号就是 n。
                 同样，蓝方制造出来的第 n 个武士，编号也是 n。武士在刚降生的时候有一个生命值。 在每个整点，双方的司
                 令部中各有一个武士降生。

                 不同的武士有不同的特点。dragon 可以拥有一件武器。编号为 n 的 dragon 降生时即获得编号为 n % 3
                 的武器。dragon 还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造
                 dragon 所需的生命元数量。ninjia 可以拥有两件武器。编号为 n 的 ninjia 降生时即获得编号为 n % 3
                 和 (n + 1) % 3 的武器。iceman 有一件武器。编号为 n 的 iceman 降生时即获得编号为 n % 3 的武
                 器。lion 有“忠诚度”这个属性，其值等于它降生后其司令部剩余生命元的数目。wolf 没特点。

                 请注意，在以后的题目里，武士的士气，生命值，忠诚度在其生存期间都可能发生变化，都有作用，武士手中的
                 武器随着使用攻击力也会发生变化。

                 武士在刚降生的时候有一个生命值。在每个整点，双方的司令部中各有一个武士降生。

                 红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序循环制造武士。蓝方司令部按照 lion、
                 dragon、ninja、iceman、wolf 的顺序循环制造武士。

                 制造武士需要生命元。制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。如果司令部中的生
                 命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司
                 令部停止制造武士。

                 给定一个时间，和双方司令部的初始生命元数目，要求你将从 0 点 0 分开始到双方司令部停止制造武士为止的
                 所有事件按顺序输出。

                 一共有两种事件，其对应的输出样例如下：
                 1) 武士降生
                 输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
                 表示在 4 点整，编号为 5 的蓝魔 lion 武士降生，它降生时生命值为 5，降生后蓝魔司令部里共有 2 个
                 lion 武士。（为简单起见，不考虑单词的复数形式）注意，每制造出一个新的武士，都要输出此时司令部里共
                 有多少个该种武士。
                 如果造出的是dragon，那么还要输出一行，例：It has a arrow,and it's morale is 23.34
                 表示该 dragon 降生时得到了 arrow，其士气是 23.34（为简单起见，本题中 arrow 前面的冠词用 a，不
                 用 an，士气精确到小数点后面 2 位，四舍五入）
                 如果造出的是 ninjia，那么还要输出一行，例：It has a bomb and a arrow
                 表示该 ninjia 降生时得到了 bomb 和 arrow。
                 如果造出的是 iceman，那么还要输出一行，例：It has a sword
                 表示该 iceman 降生时得到了 sword。
                 如果造出的是 lion，那么还要输出一行，例：It's loyalty is 24
                 表示该 lion 降生时的忠诚度是 24
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
    It has a bomb
    000 blue lion 1 born with strength 6,1 lion in blue headquarter
    It's loyalty is 14
    001 red lion 2 born with strength 6,1 lion in red headquarter
    It's loyalty is 9
    001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
    It has a arrow,and it's morale is 3.67
    002 red wolf 3 born with strength 7,1 wolf in red headquarter
    002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
    It has a sword and a bomb
    003 red headquarter stops making warriors
    003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
    It has a bomb
    004 blue headquarter stops making warriors
 *
 * @notes:
    https://stackoverflow.com/questions/36484446/defining-classes-that-contain-pointers-to-each-other
    https://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration
 * @author: Du Ang
 * @date: Aug. 27th, 2017
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

string getWeaponName(int i);
vector<string> getWarriorsProduceSequence(string color);

class Army;

class Warrior {
protected:
    int id;
    int hp;
    int attack;
    Army *army;
public:
    Warrior(Army *a, int h);
    virtual void showProperty() = 0;
};

class Dragon : public Warrior {
public:
    static const string name;
    Dragon(Army *a, int h);
    virtual void showProperty();
};

class Ninja : public Warrior {
public:
    static const string name;
    Ninja(Army *a, int h);
    virtual void showProperty();
};

class Iceman : public Warrior {
public:
    static const string name;
    Iceman(Army *a, int h);
    virtual void showProperty();
};

class Lion : public Warrior {
public:
    static const string name;
    Lion(Army *a, int h);
    virtual void showProperty();
};

class Wolf : public Warrior {
public:
    static const string name;
    Wolf(Army *a, int h);
    virtual void showProperty();
};

class Army {
protected:
    int elements;
    int warriorsCount;
    vector<Warrior *> warriors;
    vector<Dragon *> dragons;
    vector<Ninja *> ninjas;
    vector<Iceman *> icemans;
    vector<Lion *> lions;
    vector<Wolf *> wolves;
    int dragonHP, ninjaHP, icemanHP, lionHP, wolfHP;
    vector<string> warriorsProduceSequence;
    int warriorsProduceCursor;
    bool hasStoppedProducing;
public:
    string color;
    Army(string c, int M, int dHP, int nHP, int iHP, int lHP, int wHP);
    ~Army();
    bool produceOneWarrior(int time);   // true for success to produce, false for failed
    int getWarriorHealthByName(string name);
    int getWarriorsCountByName(string name);
    int getElements() { return elements; }
    void increaseWarriorCount();
    int getWarriorsTotalCount();
};

Army::Army(string c, int e, int dHP, int nHP, int iHP, int lHP, int wHP)
    : color(c), elements(e), warriorsCount(0), warriorsProduceCursor(0), hasStoppedProducing(false),
    dragonHP(dHP), ninjaHP(nHP), icemanHP(iHP), lionHP(lHP), wolfHP(wHP) {
    warriorsProduceSequence = getWarriorsProduceSequence(color);
    warriors.clear();
    dragons.clear();
    ninjas.clear();
    icemans.clear();
    lions.clear();
    wolves.clear();
}

Army::~Army() {
    for (int i = 0; i < dragons.size(); i++) {
        delete dragons.at(i);
    }
    for (int i = 0; i < ninjas.size(); i++) {
        delete ninjas.at(i);
    }
    for (int i = 0; i < icemans.size(); i++) {
        delete icemans.at(i);
    }
    for (int i = 0; i < lions.size(); i++) {
        delete lions.at(i);
    }
    for (int i = 0; i < wolves.size(); i++) {
        delete wolves.at(i);
    }
    warriors.clear();
    dragons.clear();
    ninjas.clear();
    icemans.clear();
    lions.clear();
    wolves.clear();
}

bool Army::produceOneWarrior(int t) {   // true for success, false for failure
    for (int i = 0; i < 5; i++) {
        int cursor = (warriorsProduceCursor + i) % 5;
        string warriorName = warriorsProduceSequence[cursor];
        int health = getWarriorHealthByName(warriorName);
        if (elements >= health) {
            elements = elements - health;
            warriorsProduceCursor = (cursor + 1) % 5;
            Warrior *p;
            if (warriorName == Dragon::name) {
                Dragon *dp = new Dragon(this, dragonHP);
                dragons.push_back(dp);
                p = dp;
            } else if (warriorName == Ninja::name) {
                Ninja *np = new Ninja(this, ninjaHP);
                ninjas.push_back(np);
                p = np;
            } else if (warriorName == Iceman::name) {
                Iceman *ip = new Iceman(this, icemanHP);
                icemans.push_back(ip);
                p = ip;
            } else if (warriorName == Lion::name) {
                Lion *lp = new Lion(this, lionHP);
                lions.push_back(lp);
                p = lp;
            } else if (warriorName == Wolf::name) {
                Wolf *wp = new Wolf(this, wolfHP);
                wolves.push_back(wp);
                p = wp;
            } else {
                cerr << "error: unexpected warrior name: " << warriorName << endl;
                exit(-1);
            }
            warriors.push_back(p);
            cout << setfill('0') << setw(3) << t << " ";    // print time
            p->showProperty();                              // print property
            return true;
        } else {
            continue;
        }
    }
    // can't produce warriors anymore, print stop information just for one time
    if (!hasStoppedProducing) {
        cout << setfill('0') << setw(3) << t << " ";    // print time
        cout << color << " headquarter stops making warriors" << endl;
        hasStoppedProducing = true;
    }
    return false;
}

int Army::getWarriorHealthByName(string name) {
    if (name == Dragon::name) {
        return dragonHP;
    } else if (name == Ninja::name) {
        return ninjaHP;
    } else if (name == Iceman::name) {
        return icemanHP;
    } else if (name == Lion::name) {
        return lionHP;
    } else if (name == Wolf::name) {
        return wolfHP;
    } else {
        cerr << "error: unexpected warrior name: " << name << endl;
        exit(-1);
    }
}

int Army::getWarriorsCountByName(string name) {
    if (name == Dragon::name) {
        return dragons.size();
    } else if (name == Ninja::name) {
        return ninjas.size();
    } else if (name == Iceman::name) {
        return icemans.size();
    } else if (name == Lion::name) {
        return lions.size();
    } else if (name == Wolf::name) {
        return wolves.size();
    } else {
        cerr << "error: unexpected warrior name: " << name << endl;
        exit(-1);
    }
}

void Army::increaseWarriorCount() {
    ++warriorsCount;
}

int Army::getWarriorsTotalCount() {
    return warriorsCount;
}

Warrior::Warrior(Army *a, int h) : army(a), hp(h) {
    a->increaseWarriorCount();
    id = a->getWarriorsTotalCount();
};

Dragon::Dragon(Army *a, int h) : Warrior(a, h) {}

void Dragon::showProperty() {
    cout << army->color << " " <<  name << " " << army->getWarriorsTotalCount()
        << " born with strength " << hp << "," << army->getWarriorsCountByName(name) << " " << name
        << " in " << army->color << " headquarter" << endl;
}

Ninja::Ninja(Army *a, int h) : Warrior(a, h) {}

void Ninja::showProperty() {
    cout << army->color << " " <<  name << " " << army->getWarriorsTotalCount()
        << " born with strength " << hp << "," << army->getWarriorsCountByName(name) << " " << name
        << " in " << army->color << " headquarter" << endl;
}

Iceman::Iceman(Army *a, int h) : Warrior(a, h) {}

void Iceman::showProperty() {
    cout << army->color << " " <<  name << " " << army->getWarriorsTotalCount()
        << " born with strength " << hp << "," << army->getWarriorsCountByName(name) << " " << name
        << " in " << army->color << " headquarter" << endl;
}

Lion::Lion(Army *a, int h) : Warrior(a, h) {}

void Lion::showProperty() {
    cout << army->color << " " <<  name << " " << army->getWarriorsTotalCount()
        << " born with strength " << hp << "," << army->getWarriorsCountByName(name) << " " << name
        << " in " << army->color << " headquarter" << endl;
}

Wolf::Wolf(Army *a, int h) : Warrior(a, h) {}

void Wolf::showProperty() {
    cout << army->color << " " <<  name << " " << army->getWarriorsTotalCount()
        << " born with strength " << hp << "," << army->getWarriorsCountByName(name) << " " << name
        << " in " << army->color << " headquarter" << endl;
}

string getWeaponName(int i) {
    if (i == 0) {
        return string("sword");
    } else if (i == 1) {
        return string("bomb");
    } else if (i == 2) {
        return string("arrow");
    } else {
        cerr << "error: nexpected weapon number: " << i << '\n';
        exit(-1);
    }
}

vector<string> getWarriorsProduceSequence(string color) {
    vector<string> sequence;
    if (color == "red") {
        sequence.push_back(Iceman::name);
        sequence.push_back(Lion::name);
        sequence.push_back(Wolf::name);
        sequence.push_back(Ninja::name);
        sequence.push_back(Dragon::name);
    } else if (color == "blue") {
        sequence.push_back(Lion::name);
        sequence.push_back(Dragon::name);
        sequence.push_back(Ninja::name);
        sequence.push_back(Iceman::name);
        sequence.push_back(Wolf::name);
    } else {
        cerr << "error: unexpected color of army: " << color << endl;
        exit(-1);
    }
    return sequence;
}

const string Dragon::name = "dragon";
const string Ninja::name = "ninja";
const string Iceman::name = "iceman";
const string Lion::name = "lion";
const string Wolf::name = "wolf";

int main(int argc, char const *argv[]) {
    // freopen("in.txt", "r", stdin);
    // freopen("myOut.txt", "w", stdout);

    int caseNum;
    int M;
    int dHP, nHP, iHP, lHP, wHP;
    cin >> caseNum;
    for (int i = 1; i <= caseNum; ++i) {
        cin >> M;
        cin >> dHP >> nHP >> iHP >> lHP >> wHP;
        cout << "Case:" << i << endl;
        int t = 0;
        Army redArmy("red", M, dHP, nHP, iHP, lHP, wHP);
        Army blueArmy("blue", M, dHP, nHP, iHP, lHP, wHP);
        bool redArmyProduceResult = redArmy.produceOneWarrior(t);
        bool blueArmyProduceResult = blueArmy.produceOneWarrior(t);
        t++;
        while (redArmyProduceResult || blueArmyProduceResult) {
            redArmyProduceResult = redArmy.produceOneWarrior(t);
            blueArmyProduceResult = blueArmy.produceOneWarrior(t);
            t++;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    return 0;
}
