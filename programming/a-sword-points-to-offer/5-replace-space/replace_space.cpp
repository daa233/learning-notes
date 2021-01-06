/**
 * 题目描述
 * 请实现一个函数，将一个字符串中的每个空格替换成“%20”。
 * 例如，当字符串为We Are Happy，则经过替换之后的字符串为We%20Are%20Happy。
 */

#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

// 1. 先求出修改后字符串的总长度
// 2. 设置两个指针 p1 和 p2，从后往前，分别放置到原字符串和新字符串末尾
// 3. 向前移动 p1 和 p2，p1 遇到空格，p2 向前移动三格（%20），p1、p2 相遇时结束
class Solution {
public:
	void replaceSpace(char *str, int length) {
        if (str == nullptr || length <= 0) {
            return;
        }
        int original_length = 0;
        int number_of_blank = 0;
        int i = 0;
        while (str[i] != '\0') {
            original_length++;
            if (str[i] == ' ') {
                number_of_blank++;
            }
            i++;
        }
        int new_length = original_length + number_of_blank * 2;
        if (new_length > length) {
            return;
        }
        int p1 = original_length + 1;
        int p2 = new_length + 1;
        while (p1 != p2) {
            if (str[p1] == ' ') {
                p1--;
                str[p2] = '0';
                p2--;
                str[p2] = '2';
                p2--;
                str[p2] = '%';
                p2--;
            } else {
                str[p2] = str[p1];
                p1--;
                p2--;
            }
        }
	}
};


int main(int argc, char *argv[])
{
    int length = 20;
    char str[length];
    const char *const_str = string("We Are Happy").c_str();
    strcpy(str, const_str);
    cout << "original str: " << str << endl;
    Solution s;
    s.replaceSpace(str, length);
    cout << "new str: " << str << endl;
    return 0;
}