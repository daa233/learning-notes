/**
  *  多态与虚函数 编程题＃4：魔兽世界终极版
  *
  * @file: Ultimate-WoW.cpp
  * @description: 魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，城市从
        西向东依次编号为 1, 2, 3 .... N ( N <= 20 )。红魔军的司令部算作编号为 0 的城市，蓝魔军的司令部算作编号
        为 N+1 的城市。司令部有生命元，用于制造武士。

        两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、
        攻击力这三种属性。

        双方的武士编号都是从 1 开始计算。红方制造出来的第 n 个武士，编号就是 n。同样，蓝方制造出来的第 n 个武士，编
        号也是 n。

        武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到 0（生命值变为负数时应当做变
        为 0 处理），则武士死亡（消失）。

        有的武士可以拥有武器。武器有三种：sword, bomb 和 arrow，编号分别为 0, 1, 2。

        武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有 1 个蓝武士和一个红武士），
        就会发生战斗。每次战斗只有一方发起主动进攻一次。被攻击者生命值会减去进攻者的攻击力值和进攻者手中 sword 的攻
        击力值。被进攻者若没死，就会发起反击，被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中 sword
        的攻击力值。反击可能致敌人于死地。

        如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送 8 个生命元作为奖励，使其
        生命值增加 8。当然前提是司令部得有 8 个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令
        部近的武士。
        如果某武士在某城市的战斗中杀死了敌人，则该武士的司令部立即取得该城市中所有的生命元。注意，司令部总是先完成全部
        奖励工作，然后才开始从各个打了胜仗的城市回收生命元。对于因司令部生命元不足而领不到奖励的武士，司令部也不会在取
        得战利品生命元后为其补发奖励。
        如果一次战斗的结果是双方都幸存(平局)，则双方都不能拿走发生战斗的城市的生命元。

        城市可以插旗子，一开始所有城市都没有旗子。在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。在插
        蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。
        当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有若干个战斗时刻并没有发生战斗，则这两场战斗
        仍然算是连续的；但如果中间有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，若原来插着败方的旗帜，
        则败方旗帜落下。旗帜一旦插上，就一直插着，直到被敌人更换。一个城市最多只能插一面旗帜，旗帜没被敌人更换前，也不
        会再次插同颜色的旗。

        各种武器有其特点：
        sword 武器的初始攻击力为拥有它的武士的攻击力的 20%（去尾取整）。但是 sword 每经过一次战斗(不论是主动攻击还
        是反击)，就会变钝，攻击力变为本次战斗前的 80% (去尾取整)。sword 攻击力变为 0 时，视为武士失去了 sword。如
        果武士降生时得到了一个初始攻击力为 0 的 sword，则视为武士没有 sword.
        arrow 有一个攻击力值 R。如果下一步要走到的城市有敌人，那么拥有 arrow 的武士就会放箭攻击下一个城市的敌人（不
        能攻击对方司令部里的敌人）而不被还击。arrow 使敌人的生命值减少 R，若减至小于等于 0，则敌人被杀死。arrow 使
        用 3 次后即被耗尽，武士失去 arrow。两个相邻的武士可能同时放箭把对方射死。
        拥有 bomb 的武士，在战斗开始前如果判断自己将被杀死（不论主动攻击敌人，或者被敌人主动攻击都可能导致自己被杀死，
        而且假设武士可以知道敌人的攻击力和生命值），那么就会使用 bomb 和敌人同归于尽。武士不预测对方是否会使用 bomb。
        武士使用 bomb 和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市的生命元，也不影响城市的旗帜。

        不同的武士有不同的特点。
        dragon 可以拥有一件武器。编号为 n 的 dragon 降生时即获得编号为 n%3 的武器。dragon 还有“士气”这个属性，
        是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造 dragon 所需的生命元数量。dragon 在一次在它主动进
        攻的战斗结束后，如果还没有战死，而且士气值大于 0.8，就会欢呼。dragon 每取得一次战斗的胜利(敌人被杀死)，士气
        就会增加 0.2，每经历一次未能获胜的战斗，士气值就会减少 0.2。士气增减发生在欢呼之前。
        ninjia 可以拥有两件武器。编号为 n 的 ninjia 降生时即获得编号为 n%3 和 (n+1)%3 的武器。ninja 挨打了也从
        不反击敌人。
        iceman 有一件武器。编号为 n 的 iceman 降生时即获得编号为 n%3 的武器。iceman 每前进两步，在第2步完成的时
        候，生命值会减少 9，攻击力会增加 20。但是若生命值减 9 后会小于等于 0，则生命值不减 9,而是变为 1。即 iceman
        不会因走多了而死。
        lion 有“忠诚度”这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。每经过一场未能杀死敌人的战斗，忠诚
        度就降低 K。忠诚度降至 0 或 0 以下，则该 lion 逃离战场，永远消失。但是已经到达敌人司令部的 lion 不会逃跑。
        lion 在己方司令部可能逃跑。lion 若是战死，则其战斗前的生命值就会转移到对手身上。所谓“战斗前”，就是每个小时
        的 40 分前的一瞬间。
        wolf 降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。被缴获
        的武器当然不能算新的，已经被用到什么样了，就是什么样的。

        以下是不同时间会发生的不同事件：
        在每个整点，即每个小时的第 0 分， 双方的司令部中各有一个武士降生。
        红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
        蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。

        制造武士需要生命元。制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。如果司令部中的生命元不足以
        制造某武士，那么司令部就等待，直到获得足够生命元后的第一个整点，才制造该武士。例如，在 2:00，红方司令部本该制
        造一个 wolf ，如果此时生命元不足，那么就会等待，直到生命元足够后的下一个整点，才制造一个 wolf。

        在每个小时的第 5 分，该逃跑的 lion 就在这一时刻逃跑了。
        在每个小时的第 10 分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个
        城市。或从和敌军司令部相邻的城市到达敌军司令部。
        在每个小时的第 20 分：每个城市产出 10 个生命元。生命元留在城市，直到被武士取走。
        在每个小时的第 30 分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送
        到其所属的司令部。
        在每个小时的第 35 分，拥有 arrow 的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。注意，放箭不算
        是战斗，因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。
        在每个小时的第 38 分，拥有 bomb 的武士评估是否应该使用 bomb。如果是，就用 bomb 和敌人同归于尽。
        在每个小时的第 40 分：在有两个武士的城市，会发生战斗。 如果敌人在 5 分钟前已经被飞来的 arrow 射死，那么仍然
        视为发生了一场战斗，而且存活者视为获得了战斗的胜利。此情况下不会有“武士主动攻击”，“武士反击”，“武士战死”的事
        件发生，但战斗胜利后应该发生的事情都会发生。如 wolf 一样能缴获武器，旗帜也可能更换，等等。在此情况下，dragon
        同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。
        在每个小时的第 50 分，司令部报告它拥有的生命元数量。
        在每个小时的第 55 分，每个武士报告其拥有的武器情况。

        武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。
        任何一方的司令部里若是出现了 2 个敌人，则认为该司令部已被敌人占领。
        任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。

        给定一个时间，要求你将从 0 点 0 分开始到此时间为止的所有事件按顺序输出。事件及其对应的输出样例如下：
        1) 武士降生
        输出样例： 000:00 blue lion 1 born
        表示在 0 点 0 分，编号为 1 的蓝魔 lion 武士降生

        如果造出的是 dragon，那么还要多输出一行，例：
        000:00 blue dragon 1 born
        Its morale is 23.34
        表示该 dragon 降生时士气是 23.34(四舍五入到小数点后两位)

        如果造出的是lion，那么还要多输出一行，例:
        000:00 blue lion 1 born
        Its loyalty is 24
        表示该lion降生时的忠诚度是24

        2) lion 逃跑
        输出样例： 000:05 blue lion 1 ran away
        表示在 0 点 5 分，编号为 1 的蓝魔 lion 武士逃走

        3) 武士前进到某一城市
        输出样例： 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
        表示在 0 点 10 分，红魔 1 号武士 iceman 前进到 1 号城市，此时他生命值为 20，攻击力为 30
        对于 iceman，输出的生命值和攻击力应该是变化后的数值

        4)武士放箭
        输出样例： 000:35 blue dragon 1 shot
        表示在 0 点 35 分，编号为 1 的蓝魔 dragon 武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：
        000:35 blue dragon 1 shot and killed red lion 4
        表示在 0 点 35 分，编号为 1 的蓝魔 dragon 武士射出一支箭，杀死了编号为 4 的红魔 lion。

        5)武士使用 bomb
        输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
        表示在 0 点 38 分，编号为 1 的蓝魔 dragon 武士用炸弹和编号为 7 的红魔 lion 同归于尽。

        6) 武士主动进攻
        输出样例：000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
        表示在 0 点 40 分，1 号城市中，红魔 1 号武士 iceman 进攻蓝魔 1 号武士 lion，在发起进攻前，红魔 1 号武士
        iceman 生命值为 20，攻击力为 30

        7) 武士反击
        输出样例：001:40 blue dragon 2 fought back against red lion 2 in city 1
        表示在 1 点 40 分，1 号城市中，蓝魔 2 号武士 dragon 反击红魔 2 号武士 lion

        8) 武士战死
        输出样例：001:40 red lion 2 was killed in city 1
        被箭射死的武士就不会有这一条输出。

        9) 武士欢呼
        输出样例：003:40 blue dragon 2 yelled in city 4

        10) 武士获取生命元( elements )
        输出样例：001:40 blue dragon 2 earned 10 elements for his headquarter

        11) 旗帜升起
        输出样例：004:40 blue flag raised in city 4

        12) 武士抵达敌军司令部
        输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
        (此时他生命值为 20,攻击力为 30）对于 iceman,输出的生命值和攻击力应该是变化后的数值

        13) 司令部被占领
        输出样例：003:10 blue headquarter was taken

        14)司令部报告生命元数量
        000:50 100 elements in red headquarter
        000:50 120 elements in blue headquarter
        表示在 0 点 50 分，红方司令部有 100 个生命元，蓝方有 120 个

        15)武士报告武器情况
        000:55 blue wolf 2 has arrow(2),bomb,sword(23)
        000:55 blue wolf 4 has no weapon
        000:55 blue wolf 5 has sword(20)
        表示在 0 点 55 分，蓝魔 2 号武士 wolf 有一支 arrow（这支 arrow 还可以用 2 次），一个 bomb，还有一支攻
        击力为 23 的 sword。
        蓝魔 4 号武士 wolf 没武器。
        蓝魔 5 号武士 wolf 有一支攻击力为 20 的 sword。
        交代武器情况时，次序依次是：arrow, bomb, sword。如果没有某种武器，某种武器就不用提。报告时，先按从西向东的
        顺序所有的红武士报告，然后再从西向东所有的蓝武士报告。

        输出事件时：
        首先按时间顺序输出；
        同一时间发生的事件，按发生地点从西向东依次输出. 武士前进的事件, 算是发生在目的地。

        在一次战斗中有可能发生上面的 6 至 11 号事件。这些事件都算同时发生，其时间就是战斗开始时间。一次战斗中的这些
        事件，序号小的应该先输出。

        两个武士同时抵达同一城市，则先输出红武士的前进事件，后输出蓝武士的。

        显然，13 号事件发生之前的一瞬间一定发生了 12 号事件。输出时，这两件事算同一时间发生，但是应先输出 12 号事件

        虽然任何一方的司令部被占领之后，就不会有任何事情发生了。但和司令部被占领同时发生的事件，全都要输出。

 * @input: 第一行是 t，代表测试数据组数。
        每组样例共三行。
        第一行，五个整数 M, N, R, K, T。
        其含义为：每个司令部一开始都有M个生命元( 1 <= M <= 10000)；两个司令部之间一共有N个城市( 1 <= N <= 20 )
        arrow 的攻击力是 R；lion 每经过一场未能杀死敌人的战斗，忠诚度就降低 K。
        要求输出从 0 时 0 分开始，到时间 T 为止(包括 T) 的所有事件。T 以分钟为单位，0 <= T <= 5000
        第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于 0 小于等于 10000
        第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于 0 小于等于 10000
 * @output: 对每组数据，先输出一行：Case n:
        如对第一组数据就输出 Case1:
        然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时: 分”，
        “时”有三位，“分”有两位。
 * @sample_input:
    1
    20 1 10 10 1000
    20 20 30 10 20
    5 5 5 5 5
 * @sample_output:
    Case 1:
    000:00 blue lion 1 born
    Its loyalty is 10
    000:10 blue lion 1 marched to city 1 with 10 elements and force 5
    000:30 blue lion 1 earned 10 elements for his headquarter
    000:50 20 elements in red headquarter
    000:50 20 elements in blue headquarter
    000:55 blue lion 1 has no weapon
    001:00 blue dragon 2 born
    Its morale is 0.00
    001:10 blue lion 1 reached red headquarter with 10 elements and force 5
    001:10 blue dragon 2 marched to city 1 with 20 elements and force 5
    001:30 blue dragon 2 earned 10 elements for his headquarter
    001:50 20 elements in red headquarter
    001:50 10 elements in blue headquarter
    001:55 blue lion 1 has no weapon
    001:55 blue dragon 2 has arrow(3)
    002:10 blue dragon 2 reached red headquarter with 20 elements and force 5
    002:10 red headquarter was taken
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

string getWeaponName(int i);
vector<string> getWarriorsProduceSequence(string color);

class Army;

class Timer {
private:
    int hour;
    int minute;
public:
    Timer(int h, int m) : hour(h), minute(m) {}
    Timer &operator++(int);
    int getMinute();
    void printTime();
};

Timer &Timer::operator++(int) {
    if (minute + 1 >= 60) {
        hour++;
        minute = 0;
    } else {
        minute++;
    }
    return *this;
}

int Timer::getMinute() {
    return minute;
}

void Timer::printTime() {
    cout << setfill('0') << setw(3) << hour << ":";
    cout << setfill('0') << setw(2) << minute << " ";
}

class City {
protected:
    int id;
    int elements;
    Warrior *redWarrior;
    Warrior *blueWarrior;
    string flag;
public:
    void produceElements();
};

class Warrior {
protected:
    int id;
    int hp;
    int attack;
    Army *army;
public:
    Warrior(Army *a, int h);
    virtual void marchedToCity(City *city);
    virtual void shotArrow();
    virtual void useBomb();
    virtual void attackEnemy(Warrior *enemy);
    virtual void fightBack(Warrior *enemy);
    virtual void hurted(int attack, int weaponAttack = 0);
    virtual void yell();
    virtual void getElements();
    virtual void showWeapons();
};

class Dragon : public Warrior {
private:
    int weapon;
    float morale;
public:
    static const string name;
    Dragon(Army *a, int h);
    virtual void showProperty();
};

class Ninja : public Warrior {
private:
    int firstWeapon;
    int secondWeapon;
public:
    static const string name;
    Ninja(Army *a, int h);
    virtual void showProperty();
};

class Iceman : public Warrior {
private:
    int weapon;
public:
    static const string name;
    Iceman(Army *a, int h);
    virtual void showProperty();
};

class Lion : public Warrior {
private:
    int loyalty;
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
    int enemyCount;
    vector<Warrior *> warriors;
    vector<Dragon *> dragons;
    vector<Ninja *> ninjas;
    vector<Iceman *> icemans;
    vector<Lion *> lions;
    vector<Wolf *> wolves;
    int dragonHP, ninjaHP, icemanHP, lionHP, wolfHP;
    int dragonAttack, ninjaAttack, icemanAttack, lionAttack, wolfAttack;
    vector<string> warriorsProduceSequence;
    int warriorsProduceCursor;
    int arrowAttack;
    int loyaltyDecrease;
public:
    string color;
    Army(string c, int M, int R, int K, int dHP, int nHP, int iHP, int lHP, int wHP,
        int dAttack, int nAttack, int iAttack, int lAttack, int wAttack);
    ~Army();
    void produceOneWarrior();   // true for success to produce, false for failed
    int getWarriorHealthByName(string name);
    int getWarriorsCountByName(string name);
    int getElements() { return elements; }
    void increaseWarriorCount();
    int getWarriorsTotalCount();
    void printElements();
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

void Army::produceOneWarrior() {    // true for success, false for failure
    for (int i = 0; i < 5; i++) {
        int cursor = (warriorsProduceCursor + i) % 5;
        string warriorName = warriorsProduceSequence[cursor];
        int health = getWarriorHealthByName(warriorName);
        if (elements >= health) {
            elements = elements - health;
            warriorsProduceCursor = (cursor + 1) % 5;
            Warrior *p;
            if (warriorName == Dragon::name) {
                Dragon *dp = new Dragon(this, dragonHP, dragonAttack);
                dragons.push_back(dp);
                p = dp;
            } else if (warriorName == Ninja::name) {
                Ninja *np = new Ninja(this, ninjaHP, ninjaAttack);
                ninjas.push_back(np);
                p = np;
            } else if (warriorName == Iceman::name) {
                Iceman *ip = new Iceman(this, icemanHP, icemanAttack);
                icemans.push_back(ip);
                p = ip;
            } else if (warriorName == Lion::name) {
                Lion *lp = new Lion(this, lionHP, lionAttack);
                lions.push_back(lp);
                p = lp;
            } else if (warriorName == Wolf::name) {
                Wolf *wp = new Wolf(this, wolfHP, wolfAttack);
                wolves.push_back(wp);
                p = wp;
            } else {
                cerr << "error: unexpected warrior name: " << warriorName << endl;
                exit(-1);
            }
            warriors.push_back(p);
        } else {
            continue;
        }
    }
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

Dragon::Dragon(Army *a, int h)
    : Warrior(a, h),
    weapon(army->getWarriorsTotalCount() % 3),
    morale(double(army->getElements()) / hp) {}

void Dragon::showProperty() {
    cout << army->color << " " <<  name << " " << id << " born" << endl;
    cout << "Its morale is ";
    cout << fixed << setprecision(2) << morale << endl;
}

Ninja::Ninja(Army *a, int h)
    : Warrior(a, h),
    firstWeapon(army->getWarriorsTotalCount() % 3),
    secondWeapon((army->getWarriorsTotalCount() + 1) % 3) {}

void Ninja::showProperty() {
    cout << army->color << " " <<  name << " " << id << " born" << endl;
}

Iceman::Iceman(Army *a, int h) : Warrior(a, h), weapon(army->getWarriorsTotalCount() % 3) {}

void Iceman::showProperty() {
    cout << army->color << " " <<  name << " " << id << " born" << endl;
}

Lion::Lion(Army *a, int h) : Warrior(a, h), loyalty(army->getElements()) {}

void Lion::showProperty() {
    cout << army->color << " " <<  name << " " << id << " born" << endl;
    cout << "It's loyalty is " << loyalty << endl;
}

Wolf::Wolf(Army *a, int h) : Warrior(a, h) {}

void Wolf::showProperty() {
    cout << army->color << " " <<  name << " " << id << " born" << endl;
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
    int M, N, R, K, T;
    int dHP, nHP, iHP, lHP, wHP;
    int dAttack, nAttack, iAttack, lAttack, wAttack;
    cin >> caseNum;
    for (int i = 1; i <= caseNum; ++i) {
        cin >> M >> N >> R >> K >> T;
        cin >> dHP >> nHP >> iHP >> lHP >> wHP;
        cin >> dAttack >> nAttack >> iAttack >> lAttack >> wAttack;
        cout << "Case:" << i << endl;
        Timer t(0, 0);
        Army redArmy("red", M, N, R, K, T, dHP, nHP, iHP, lHP, wHP, dAttack, nAttack, iAttack,
                    lAttack, wAttack);
        Army blueArmy("blue", M, N, R, K, T, dHP, nHP, iHP, lHP, wHP, dAttack, nAttack, iAttack,
                    lAttack, wAttack);

        while (true) {
            t.printTime();
            switch (t.getMinute()) {
                case 0:
                    // produceOneWarrior
                    redArmy.produceOneWarrior()
                    break;
                case 5:
                    // lion run away
                    break;
                case 10:
                    // marched a step
                    break;
                case 20:
                    // each city produce 10 elements
                    break;
                case 30:
                    // warrior take elements of the city
                    break;
                case 35:
                    // shoot arrow
                    break;
                case 38:
                    // use bomb
                    break;
                case 40:
                    // fight and win the loot
                    break;
                case 50:
                    // headquarter print elements
                    break;
                case 55:
                    // warrior report their weapons
                    break;
                default:
                    breakl;
            }
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    return 0;
}
