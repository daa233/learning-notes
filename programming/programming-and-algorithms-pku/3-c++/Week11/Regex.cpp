/**
 * @file: Regex.cpp
 * @description: C++11 新特性，正则表达式
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 4th, 2017
 */

#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char const *argv[]) {
    regex reg("b.?p.*k");
    // . matches any single character
    // ? indicates zero or one occurrences of the preceding element
    // * indicates zero or more occurrences of the preceding element
    cout << regex_match("bopggk", reg) << endl;             // 1 (matched)
    cout << regex_match("boopgggk", reg) << endl;           // 0 (not matched)
    cout << regex_match("b pk", reg) << endl;               // 1 (matched)
    regex reg2("\\d{3}([a-zA-Z]+).(\\d{2}|N/A\\s\\1)");
    // \\d matches any signle digit
    // {n} the preceding item is matched exactly n times
    // () defines a marked subexpression
    // [] matches a single character that is contained within the brackets
    // + indicates one or more occurrences of the preceding element
    // | matches either the expression before or the expression after the operator
    // \\s matches a whitespace character
    // \\n matches what the nth marked subexpression matched, n is a digit from 1 to 9
    string correct = "123Hello N/A Hello";
    string incorrect = "123Hello 12 hello";
    cout << regex_match(correct, reg2) << endl;             // 1 (matched)
    cout << regex_match(incorrect, reg2) << endl;           // 0 (not matched)
    return 0;
}
