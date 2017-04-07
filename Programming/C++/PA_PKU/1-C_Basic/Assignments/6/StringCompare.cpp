/**
 * C程序中的数组 数组应用练习 编程题 #2：忽略大小写比较字符串大小
 *
 * @file: StirngCompare.cpp
 * @description: 一般我们用strcmp可比较两个字符串的大小，比较方法为对两个字符串从前往后逐个字符相比较（按ASCII码值大小比较），
                直到出现不同的字符或遇到'\0'为止。如果全部字符都相同，则认为相同；如果出现不相同的字符，则以第一个不相同的字符的
                比较结果为准。但在有些时候，我们比较字符串的大小时，希望忽略字母的大小，例如"Hello"和"hello"在忽略字母大小写时
                是相等的。请写一个程序，实现对两个字符串进行忽略字母大小写的大小比较。
 * @input: 输入为两行，每行一个字符串，共两个字符串。（请用cin.getline(s,80)录入每行字符串）（每个字符串长度都小于80）
 * @output: 如果第一个字符串比第二个字符串小，输出一个字符"<";如果第一个字符串比第二个字符串大，输出一个字符">";
            如果两个字符串相等，输出一个字符"="
 * 样例输入
    第一组
    Hello
    hello
    第二组
    hello
    HI
    第三组
    hello
    HELL
 * 样例输出
    第一组
    =
    第二组
    <
    第三组
    >
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

 #include <iostream>

 using namespace std;

 int main(int argc, char *argv[])
 {
     const int counts = 80;   // 定义字符串最大长度
     char str1[counts];  // str1[]存储字符串1
     char str2[counts];  // str2[]存储字符串2
     char result = '0';  // 存储最后的结果
     cin.getline(str1, counts);  // 输入字符串str1
     cin.getline(str2, counts);  // 出入字符串str2
     int i = 0;

     // 比较前，把每个大写字母都转换成小写字母(查ASCII表可知，需加32)
     for (i = 0; i < counts; i++) {
         if (str1[i] >= 65 && str1[i] <= 90) {
             str1[i] = str1[i] + 32;     // 将str1中的大写字母转换为小写
         }
         if (str2[i] >= 65 && str2[i] <= 90) {
             str2[i] = str2[i] + 32;     // 将str2中的大写字母转换为小写
         }
     }
     // 利用提示中的strcmp()的方法比较str1和str2
     i = 0;  // 将i清零
     while (str1[i] != '\0' && (str1[i] == str2[i])) {
         i++;
     }
     if (str1[i] > str2[i]) {
         result = '>';
     } else if (str1[i] < str2[i]) {
         result = '<';
     } else{
         result = '=';
     }
     cout << result << endl;

     return 0;
 }
