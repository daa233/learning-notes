/**
 * C程序中的数组 数组应用练习 编程题 #1：字母的个数
 *
 * @file: CharsNumbers.cpp
 * @description: 在一个字符串中找出元音字母a,e,i,o,u出现的次数。
 * @input: 输入一行字符串（字符串中可能有空格，请用gets(s)方法把一行字符串输入到字符数组s中），字符串长度小于80个字符。
 * @output: 输出一行，依次输出a,e,i,o,u在输入字符串中出现的次数，整数之间用空格分隔。
 * 样例输入
    If so, you already have a Google Account. You can sign in on the right.
 * 样例输出
    5 4 3 7 3
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

 #include <iostream>

 using namespace std;

 int main(int argc, char *argv[])
 {
     const int counts = 80;  // 定义字符串最大长度
     char s[counts] = "";    // 存储用户输入的字符串
     int num[5] = {0};       // num[0]到num[4]分别存储a, e, i, o, u出现的次数，初始化为全0
     cin.getline(s, counts);

     for (int i = 0; i < counts; i++) {
         switch (s[i]) {
             case 'a':
                 num[0]++;
                 break;
             case 'e':
                 num[1]++;
                 break;
             case 'i':
                 num[2]++;
                 break;
             case 'o':
                 num[3]++;
                 break;
             case 'u':
                 num[4]++;
                 break;
             default:
                 break;
         }
     }
     // 输出最后的结果
     for (int i = 0; i < 5; i++) {
         cout << num[i] << " ";
     }
     cout << endl;
     return 0;
 }
