/**
 * 递归编程练习 编程题 #3：排队游戏
 *
 * @file: QueuingGame.cpp
 * @description: 在幼儿园中，老师安排小朋友做一个排队的游戏。首先老师精心的把数目相同的小男孩和小女孩编排在一个队列中，每个小孩按其在队列
                中的位置发给一个编号（编号从0开始）。然后老师告诉小朋友们，站在前边的小男孩可以和他后边相邻的小女孩手拉手离开队列，剩余的
                小朋友重新站拢，再按前后相邻的小男孩小女孩手拉手离开队列游戏，如此往复。由于教师精心的安排，恰好可以保证每两个小朋友都能手
                拉手离开队列，并且最后离开的两个小朋友是编号最小的和最大的两个小朋友。（注：只有小男孩在前，小女孩在后，且他们两之间没有其
                他的小朋友，他们才能手拉手离开队列）。请根据老师的排队，按小女孩编号从小到大的顺序，给出 所有手拉手离开队列的小男孩和小女孩
                的编号对。
 * @input: 用一个字符串代表小朋友队列。字符串中只会出现两个字符（样例输入里用的是 括号但实际数据则不一定），分别代表小男孩和小女孩，首先出现
        的字符代表小男孩，另一个字符代表小女孩。小孩总数不超过100。
 * @output: 按小女孩编号顺序，顺序输出手拉手离开队列的小男孩和小女孩的编号对，每行一对编号，编号之间用一个空格分隔。
 * 样例输入
    ((()(())())(()))
 * 样例输出
    2 3
    5 6
    4 7
    8 9
    1 10
    12 13
    11 14
    0 15
 *
 * @author: Du Ang
 * @date: Apr. 20th, 2017
 */

#include <iostream>

using namespace std;

int f(char str[], int index);

/* 可以看作是“简单括号匹配问题”的变式，但这里的情况是一定可以匹配，打印匹配过程。以下的思路是：先假设一个函数f(char str[], int index)可以
   解决这个问题，然后利用这个函数f(str[], index)进行分析。如果index处是个男孩，则需要找到他后面的女孩的位置，所以递归调用自己来寻找，
   并打印，而且下面需要从刚找到的女孩后面继续遍历，直到队伍末尾；如果index处是个女孩，则返回index。
   我在做这道题时，还有另一个思路，也是想分层来考虑，每一层都将前面的男生的位置(preBoyIdx)传递进来，找到女生后进行根据前面男生的位置进行打印，然后跳出这一层。
   问题是，找到女生位置时再打印，这个女生前面的男生位置可以知道，但跳出这层循环后，需要再次递归调用自身，但是前面的前面男生的位置是不知道的，所以没有走通。
*/
int f(char str[], int index)
{
    char boyChar = str[0];
    if (str[index] != boyChar) {
        return index;   // index处是女孩，返回女孩的位置（也可能是'\0'，此时退出递归）
    } else {
        int girlIndex = f(str, index+1);    // index处是男孩，返回它后面的女孩的位置，并打印
        cout << index << " " << girlIndex << endl;
        return f(str, girlIndex+1); // 这一步最关键，我开始时错在将girlIndex写成了index
    }
}

/*
int fun(char str[], int index, int preBoyIdx)
{
    char boyChar = str[0];
    if (str[index] != boyChar) {
        cout << preBoyIdx << " " << index << endl;
        f(str, index+1, )   // 无法得知上层前面男生的位置
    } else {
        f(str, index+1, index);
    }
}*/

int main(int argc, char const *argv[]) {
    char str[100];
    cin >> str;
    f(str, 0);
    return 0;
}
