/**
 * 期末考试 编程题＃2：字符串中次数第 2 多的字母（未在 OpenJudge 上找到对应题目）
 *
 * @file: TheSecondMostLetterInString.cpp
 * @description: 输入一串长度不超过 500 个符号的字符串，输出在串中出现第 2 多的英语字母(大小写字母认为相同)和次数
                （如果串中有其它符号，则忽略不考虑）。如果有多个字母的次数都是第 2 多，则按串中字母出现的顺序输出
                第 1 个。
                例 ab&dcAab&c9defgb，这里，a 和 b 都出现 3 次，c 和 d 都出现 2 次，e、f 和 g 各出现 1 次，
                其中的符号 & 和 9 均忽略不考虑。因此，出现第 2 多的应该是 c 和 d，但是 d 开始出现的位置在 c 的
                前面，因此，输出为 D+d:2
                (假定在字符串中，次数第 2 多的字母总存在)
 * @input: 一个字符串
 * @output: 大写字母+小写字母:个数
 * @sample_input:
    ab&dcAab&c9defgb
 * @sample_output:
    D+d:2
 *
 * @author: Du Ang
 * @date: Aug. 10th, 2017
 */

#include <iostream>

using namespace std;

struct letterCount {
    char letter;
    int count;
    letterCount *next;
};

void checkToAdd(letterCount *head, char c)
{
    letterCount *temp = head;
    while (temp->next != NULL) {
        if (temp->letter == c) {
            temp->count = temp->count + 1;
        }
        temp = temp->next;
    }
    // now *temp points to the last node
    if (temp->letter == c) {
        temp->count = temp->count + 1;
    } else {
        temp->next = new letterCount;
        temp->next->letter = c;
        temp->next->count = 1;
        temp->next->next = NULL;
    }
}

int main(int argc, char const *argv[]) {
    char s[500];
    int size = 0;
    letterCount *head = new letterCount;
    head->count = 0;
    head->next = NULL;
    cin >> s;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 65 && s[i] <= 90) {
            if (i == 0) {
                head->letter = s[i] + 32;
                head->count = head->count + 1;
            } else {
                checkToAdd(head, s[i] + 32);
            }
        } else if (s[i] >= 97 && s[i] <= 122) {
            if (i == 0) {
                head->letter = s[i];
                head->count = head->count + 1;
            } else {
                checkToAdd(head, s[i]);
            }
        }
    }
    /*
    while (temp->next != NULL) {
        cout << temp->letter << ": " << temp->count << endl;
        temp = temp->next;
    }
    cout << temp->letter << ": " << temp->count << endl;
    */
    letterCount *temp = head;
    int maxCount[2] = {0, 0};
    char maxLetter[2];
    maxCount[0] = head->count;
    maxLetter[0] = head->letter;
    while (temp->next != NULL) {
        if (temp->next->count > maxCount[0]) {
            maxCount[0] = temp->next->count;
            maxLetter[0] = temp->next->letter;
        } else if (temp->next->count < maxCount[0] && temp->next->count > maxCount[1]) {
            maxCount[1] = temp->next->count;
            maxLetter[1] = temp->next->letter;
        }
        temp = temp->next;
    }
    cout << (char)(maxLetter[1] - 32) << "+" << maxLetter[1] << ":"<< maxCount[1] << endl;
    return 0;
}
