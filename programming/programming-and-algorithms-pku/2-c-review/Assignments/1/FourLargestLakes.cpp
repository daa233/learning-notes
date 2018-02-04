/**
 * 综合编程练习（1）编程题 #2：四大湖
 *
 * @file: FourLargestLakes.cpp
 * @description: 我国有4大淡水湖。
                    A说：洞庭湖最大，洪泽湖最小，鄱阳湖第三。
                    B说：洪泽湖最大，洞庭湖最小，鄱阳湖第二，太湖第三。
                    C说：洪泽湖最小，洞庭湖第三。
                    D说：鄱阳湖最大，太湖最小，洪泽湖第二，洞庭湖第三。
                已知这4个湖的大小均不相等，4个人每人仅答对一个，请编程按照鄱阳湖、洞庭湖、太湖、洪泽湖的顺序给出他们的大小排名。
 * @input: 无
 * @output: 输出为4行，第1行为鄱阳湖的大小名次，从大到小名次分别表示为1、2、3、4；第2、3、4行分别为洞庭湖、太湖、洪泽湖的大小名次。
 * 样例输入
    (无)
 * 样例输出 (样例输出仅供格式参考，此题只有一个解。)
    3
    2
    1
    4
 *
 * @author: Du Ang
 * @date: Apr. 16th, 2017
 */

#include <iostream>

using namespace std;

bool checkPropositions(int lakes[]);

int main(int argc, char *argv[])
{
    int lakes[4] = {0};     // lakes[0]——lakes[3]分别表示鄱阳湖、洞庭湖、太湖、洪泽湖的排行

    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 5; j++) {
            for (int k = 1; k < 5; k++) {
                for (int l = 1; l < 5; l++) {
                    if (i == j || i == k || i == l || j == k || j== l || k == l)
                        continue;
                    lakes[0] = i;
                    lakes[1] = j;
                    lakes[2] = k;
                    lakes[3] = l;
                    if (checkPropositions(lakes)) {
                        for (int m = 0; m < 4; m++)
                            cout << lakes[m] << endl;
                    } else {
                        continue;
                    }
                }
            }
        }
    }

    return 0;
}

bool checkPropositions(int lakes[])
{
    bool p[4][4] = {false};
    p[0][0] = lakes[1] == 1; p[0][1] = lakes[3] == 4; p[0][2] = lakes[0] == 3;
    p[1][0] = lakes[3] == 1; p[1][1] = lakes[1] == 4; p[1][2] = lakes[0] == 2;
    p[1][3] = lakes[2] == 3;
    p[2][0] = lakes[3] == 4; p[2][1] = lakes[1] == 3;
    p[3][0] = lakes[0] == 1; p[3][1] = lakes[2] == 4; p[3][2] = lakes[3] == 2;
    p[3][3] = lakes[1] == 3;
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (int j = 0; j < 4; j++) {
            if (p[i][j]) count++;
        }
        if (count != 1) {
            return false;
        }
    }
    return true;
}
