/**
 * @file: HanoiTower.cpp
 * @description: 相传在古代印度的Bramah庙中，有位僧人整天把三根柱子上的金盘倒来倒去，他想把64个一个比一个小的金盘从一根柱子上移到另
                一根柱子上去。移动过程中恪守下述规则：每次只允许移动一只盘，且大盘不得落在小盘上面。
                现三根柱子分别为A、B、C，最初所有的盘子都在柱子A上，需要将它们全部移动到柱子C上。输入盘子数目，打印移动过程。
 * @solution: 将n个盘子从A移动到C，等价于先把A上的n-1个盘子从A移动到B，再把第n个盘子从A移动到C，最后把n-1个盘子从B移动到C
 *
 * @author: Du Ang
 * @date: Apr. 17th, 2017
 */

#include <iostream>

using namespace std;

// 将 m 个盘子从x，经过y，移动到z
void move(int m, char x, char y, char z)
{
    if (m == 1) {
        cout << "Move one disk from rod " << x << " to rod " << z << endl;
    } else {
        move(m-1, x, z, y);
        cout << "Move one disk from rod " << x << " to rod " << z << endl;
        move(m-1, y, x, z);
    }
}

int main(int argc, char const *argv[]) {
    int n;
    cout << "Please input the number of disks: ";
    cin >> n;
    cout << "The steps of moving " << n << " disks on three rods: " << endl;
    move(n, 'A', 'B', 'C');
    return 0;
}
