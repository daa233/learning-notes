/**
 *  文件操作和模板 编程题＃4
 *
 * @file: Week7Ex4.cpp
 * @description: 给定 n 个字符串（从1开始编号），每个字符串中的字符位置从 0 开始编号，长度为 1-500，现有如下若干
                操作：
                copy N X L：取出第 N 个字符串第 X 个字符开始的长度为 L 的字符串。
                add S1 S2：判断 S1，S2 是否为 0-99999 之间的整数，若是则将其转化为整数做加法，若不是，则作字符
                        串加法，返回的值为一字符串。
                find S N：在第 N 个字符串中从左开始找寻 S 字符串，返回其第一次出现的位置，若没有找到，返回字符串
                        的长度。
                rfind S N：在第 N 个字符串中从右开始找寻 S 字符串，返回其第一次出现的位置，若没有找到，返回字符串
                的长度。
                insert S N X：在第 N 个字符串的第 X 个字符位置中插入 S 字符串。
                reset S N：将第 N 个字符串变为 S。
                print N：打印输出第 N 个字符串。
                printall：打印输出所有字符串。
                over：结束操作。
            其中 N，X，L可由 find 与 rfind 操作表达式构成，S，S1，S2 可由 copy 与 add 操作表达式构成。
 * @input: 第一行为一个整数 n（ n 在 1-20 之间），接下来 n 行为 n 个字符串，字符串不包含空格及操作命令等。
        接下来若干行为一系列操作，直到 over 结束。
 * @output: 根据操作提示输出对应字符串。
 * @sample_input:
    3
    329strjvc
    Opadfk48
    Ifjoqwoqejr
    insert copy 1 find 2 1 2 2 2
    print 2
    reset add copy 1 find 3 1 3 copy 2 find 2 2 2 3
    print 3
    insert a 3 2
    printall
    over
 * @sample_output:
    Op29adfk48
    358
    329strjvc
    Op29adfk48
    35a8
 * @hint: 推荐使用 string 类中的相关操作函数。
 *
 * @author: Du Ang
 * @date: Aug. 26th, 2017
 */

#include <iostream>
#include <string>
#include <stdlib.h> // for atoi

using namespace std;

string copy(string *strArray, int n, int x, int l) {
    return strArray[n-1].substr(x, l);
}

string add(string s1, string s2) {
    // check if s1 and s2 only contain numbers, if not, return s1 + s2
    // note: atoi(83s) will return 83!
    // refered to: http://blog.csdn.net/nnnnnnnnnnnny/article/details/50533970
    for (int i = 0; i < s1.size(); i++) {
        if (s1.at(i) < '0' || s1.at(i) > '9') {
            return s1 + s2;
        }
    }
    for (int i = 0; i < s2.size(); i++) {
        if (s2.at(i) < '0' || s2.at(i) > '9') {
            return s1 + s2;
        }
    }
    // s1 and s2 only contain numbers
    long a = atoi(s1.c_str());
    long b = atoi(s2.c_str());
    if (a >= 0 && a <= 99999 && b >= 0 && b <= 99999) {
        long c = a + b;
        return to_string(c);
    } else {
        return s1 + s2;
    }
}

string find(string *strArray, string s, int n) {
    unsigned long index = strArray[n-1].find(s);
    if (index == string::npos) {    // not found
        return to_string(s.length());
    } else {                        // found
        return to_string(index);
    }
}

string rfind(string *strArray, string s, int n) {
    unsigned long index = strArray[n-1].rfind(s);
    if (index == string::npos) {    // not found
        return to_string(s.length());
    } else {                        // found
        return to_string(index);
    }
}

string insert(string *strArray, string s, int n, int x) {
    strArray[n-1].insert(x, s);
    return string();
}

string reset(string *strArray, string s, int n) {
    strArray[n-1] = s;
    return string();
}

string notation(string *strArray, string &cmd) {
    unsigned long blankIndex;
    blankIndex = cmd.find_first_of(' ');
    if (blankIndex == string::npos) {   // only one operand left in the string cmd
        return cmd;                     // return the last operand
    } else {                            // more than one operands left in the string cmd
        string head = cmd.substr(0, blankIndex);
        if (head == "copy") {           // three operands (int, int, int) return string
            cmd = cmd.substr(blankIndex + 1);
            string nString = notation(strArray, cmd);
            string xString = notation(strArray, cmd);
            string lString = notation(strArray, cmd);
            int n = atoi(nString.c_str());
            int x = atoi(xString.c_str());
            int l = atoi(lString.c_str());
            // clog << "n = " << n << ", x = " << x << ", l = " << l << endl;
            return copy(strArray, n, x, l);
        } else if (head == "add") {     // two operands (string, string), return string
            cmd = cmd.substr(blankIndex + 1);
            string s1 = notation(strArray, cmd);
            string s2 = notation(strArray, cmd);
            return add(s1, s2);
        } else if (head == "find") {    // two operands (string, int), return int
            cmd = cmd.substr(blankIndex + 1);
            string targetStr = notation(strArray, cmd);
            string nString = notation(strArray, cmd);
            int n = atoi(nString.c_str());
            return find(strArray, targetStr, n);
        } else if (head == "rfind") {   // two operands (string , int), return int
            cmd = cmd.substr(blankIndex + 1);
            string targetStr = notation(strArray, cmd);
            string nString = notation(strArray, cmd);
            int n = atoi(nString.c_str());
            return rfind(strArray, targetStr, n);
        } else if (head == "insert") {  // three operands (string, int, int), return void
            cmd = cmd.substr(blankIndex + 1);
            string s = notation(strArray, cmd);
            string nString = notation(strArray, cmd);
            string xString = notation(strArray, cmd);
            int n = atoi(nString.c_str());
            int x = atoi(xString.c_str());
            return insert(strArray, s, n, x);
        } else if (head == "reset") {   // two operands (string, int), return void
            cmd = cmd.substr(blankIndex + 1);
            string s = notation(strArray, cmd);
            string nString = notation(strArray, cmd);
            int n = atoi(nString.c_str());
            return reset(strArray, s, n);
        } else if (head == "print") {   // one operands (int), return void
            cmd = cmd.substr(blankIndex + 1);
            string indexStr = notation(strArray, cmd);
            int i = atoi(indexStr.c_str());
            cout << strArray[i-1] << endl;
            return string();
        } else {                        // head is a operand, return it and continue
            cmd = cmd.substr(blankIndex + 1);
            return head;
        }
    }
}

int main(int argc, char const *argv[]) {
   // freopen("in.txt", "r", stdin);
   // freopen("myOut.txt", "w", stdout);

    int n;
    cin >> n;
    string strArray[n];
    for (int i = 0; i < n; i++) {
        cin >> strArray[i];
    }

    while (true) {
        string cmd;
        getline(cin, cmd, '\n');
        if (cmd == "over") {    // no operands
            break;
        } else {
            // parse and execute the command in this line
            if (!cmd.empty()) {
                if (cmd == "printall") { // no operands
                    for (int i = 0; i < n; i++) {
                        cout << strArray[i] << endl;
                    }
                } else {    // have operands. just as Reverse Polish Notation
                    notation(strArray, cmd);
                }
            }
        }
    }

   // fclose(stdin);
   // fclose(stdout);

    return 0;
}
