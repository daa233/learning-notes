/**
 * @file: PolymorphismGameSample.cpp
 * @description: 使用多态的游戏程序实例——游戏《魔法门之英雄无敌》
                游戏中有很多怪物，如战士、龙、凤凰、天使等，每种怪物都有一个类与之对应，每个怪物就是一个对象。
                怪物能够互相攻击，攻击敌人和被攻击时都有相应的动作，动作是通过对象的成员函数实现的。
                在游戏版本升级时，要增加新的怪物——雷鸟。如何编程才能使升级时的代码改动和增加量较小？
                基本思路：
                为每个怪物类编写 attack、fightBack 和 hurted 成员函数。其中 attack 函数表现攻击动作，攻击某个
                怪物，并调用被攻击怪物的 hurted 函数，以减少被攻击怪物的生命值，同时也调用被攻击怪物的 fightBack
                成员函数，遭受被攻击怪物反击。
                hurted 函数减少自身生命值，并表现受伤动作。
                fightBack 成员函数表现反击动作，并调用被反击对象的 hurted 成员函数，使被反击对象受伤。
                设置基类 CCreature，并且使 CDragon，CWolf 等其他类都从 CCreature 派生而来。
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 23rd, 2017
 */

#include <iostream>

using namespace std;

/*************** start non-polymorphism way ***************/
/**
 * 有 n 种怪物，CDragon 类中就会有 n 个 attack 成员函数，以及 n 个 fightback 成员函数。对于其他类也如此。
 * 如果游戏版本升级，增加了怪物雷鸟 CThunderBird，则程序改动较大。
 * 所有的类都需要增加两个成员函数：
 *  void attack(CThunderBird *pThunderBird);
 *  void fightBack(CThunderBird *pThunderBird);
 * 在怪物种类多的时候，工作量将巨大无比！
 */
class CCreatureNP {
protected:
    int nPower;     // attack
    int nLifeValue; // life
};

class CDragonNP : public CCreatureNP {
public:
    void attack(CWolf *pWolf) {
        // some attack codes
        pWolf->hurted(nPower);
        pWolf->fightBack(this);
    }
    void attack(CGhost *pGhost) {
        // some attack codes
        pGhost->hurted(nPower);
        pGhost->fightBack(this);
    }
    void hurted(int nPower) {
        // some hurted codes
        nLifeValue -= nPower;
    }
    void fightBack(CWolf *pWolf) {
        // some fight back codes
        pWolf->hurted(nPower / 2);
    }
    void fightBack(CGhost *pGhost) {
        // some fightBack codes
        pGhost->hurted(nPower / 2);
    }
};
/*************** end non-polymorphism way ***************/

/*************** start polymorphism way ***************/
/**
 * 基类 CCreature 只有一个 attack 成员函数；也只有一个 fightBack 成员函数；所有 CCreature 的派生类也是这样。
 * 如果游戏版本升级，增加了新的怪物雷鸟 CThunderBird，只需要编写新类 CThunderBird，不需要在已有的类里专门为新怪物
 * 增加：
 *  void attack(CThunderBird *pThunderBird);
 *  void fightBack(CThunderBird *pThunderBird);
 * 成员函数，已有的类可以原封不动！
 */
class CCreature {
protected:
    int mLifeValue, mPower;
public:
    virtual void attack(CCreature *pCreature) {}
    virtual void hurted(int mPower) {}
    virtual void fightBack(CCreature *pCreature) {}
};

class CDragon : public CCreature {
public:
    virtual void attack(CCreature *pCreature);
    virtual void hurted(CCreature *pCreature);
    virtual void fightBack(CCreature *pCreature);
};

void CDragon::attack(CCreature *p) {
    // some attack codes
    p->hurted(mPower);
    p->fightBack(this);
}

void CDragon::hurted(int nPower) {
    // some hurted codes
    mLifeValue -= nPower;
}

void CDragon::fightBack(CCreature *p) {
    // some fight back codes
    p->hurted(mPower / 2);
}

/*************** end polymorphism way ***************/

int main(int argc, char const *argv[]) {
    CDragon dragon;
    CWolf wolf;
    CGhost ghost;
    CThunderBird thunderBird;
    dragon.attack(&wolf);           // CWolf::hurted ...
    dragon.attack(&ghost);          // CGhost::hurted ...
    dragon.attack(&thunderBird);    // CThunderBird::hurted ...
    return 0;
}
