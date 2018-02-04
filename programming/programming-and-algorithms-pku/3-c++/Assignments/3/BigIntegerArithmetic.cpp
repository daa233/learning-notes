/**
  *  运算符重载 编程题＃4：大整数的加减乘除
  *
  * @file: BigIntegerArithmetic.cpp
  * @description: 给出两个正整数以及四则运算操作符（+ - * /），求运算结果。
                补充说明：
                1. 减法结果有可能为负数
                2. 除法结果向下取整
                3. 输出符合日常书写习惯，不能有多余的0、空格或其它字符
 * @input:
    第一行：正整数 a，长度不超过 100
    第二行：四则运算符 o，o 是“+”，“-”，“*”，“/”中的某一个
    第三行：正整数 b，长度不超过 100
    保证输入不含多余的空格或其它字符
 * @output: 一行：表达式“a o b”的值。
 * @sample_input:
    9876543210
    +
    9876543210
 * @sample_output:
    19753086420
 *
 * @author: Du Ang
 * @date: Aug. 21st, 2017
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>      // for atoi()
#include <algorithm>    // for reverse()

using namespace std;

class BigInt {
private:
    vector<int> digit;
    bool sign;  // the sign digit, true for positive, false for negative
public:
    BigInt();
    BigInt(string s);
    BigInt(vector<int> v);
    BigInt(const BigInt &bi);
    ~BigInt();
    BigInt &operator=(const BigInt &bi);
    BigInt operator+(const BigInt &a);
    BigInt operator-(const BigInt &a);
    BigInt operator*(const BigInt &a);
    BigInt operator/(const BigInt &a);
    friend ostream &operator<<(ostream &os, const BigInt &bi);
    friend istream &operator>>(istream &is, BigInt &bi);
    int compareWith(const BigInt &a);   // 1 for >, 0 for ==, -1 for <
};

BigInt::BigInt() : sign(true) {
    digit.clear();
}

BigInt::BigInt(string s) : sign(true) {
    digit.clear();
    for (int i = s.size() - 1; i >= 0; i--) {
        const char *tmp = (s.substr(i, 1)).c_str();
        int n = atoi(tmp);
        digit.push_back(n);
    }
}

BigInt::BigInt(vector<int> v) : digit(v), sign(true) {}

BigInt::BigInt(const BigInt &bi) {
    digit = bi.digit;
    sign = bi.sign;
}

BigInt::~BigInt() {
    digit.clear();
}

BigInt &BigInt::operator=(const BigInt &bi) {
    digit.clear();
    digit = bi.digit;
    sign = bi.sign;
    return *this;
}

BigInt BigInt::operator+(const BigInt &a) {
    BigInt result;
    int i = 0;
    int carry = 0;
    int tempSum = 0;
    for (i = 0; i < digit.size() && i < a.digit.size(); i++) {
        tempSum = digit[i] + a.digit[i] + carry;
        if (tempSum >= 10) {
            result.digit.push_back(tempSum % 10);
            carry = 1;
        } else {
            result.digit.push_back(tempSum);
            carry = 0;
        }
    }
    if (i < digit.size()) { // *this has more digits
        for ( ; i < digit.size(); i++) {
            tempSum = digit[i] + carry;
            if (tempSum >= 10) {
                result.digit.push_back(tempSum % 10);
                carry = 1;
            } else {
                result.digit.push_back(tempSum);
                carry = 0;
            }
        }
    } else if (i < a.digit.size()) {    // a has more digits
        for ( ; i < a.digit.size(); i++) {
            tempSum = a.digit[i] + carry;
            if (tempSum >= 10) {
                result.digit.push_back(tempSum % 10);
                carry = 1;
            } else {
                result.digit.push_back(tempSum);
                carry = 0;
            }
        }
    } else {}   // *this and a has the same digits
    if (carry > 0) {
        result.digit.push_back(carry);
    }
    return result;
}

BigInt BigInt::operator-(const BigInt &a) {
    BigInt result;
    // judge the sign digit
    int compareCode = this->compareWith(a);
    if (compareCode == 1) {
        result.sign = true;
    } else if (compareCode == 0) {
        result.digit.push_back(0);
        return result;
    } else {    // same length
        result.sign = false;
    }
    // get the difference
    if (result.sign) {  // the difference is positive
        int tempDiff;
        int borrowDigit = 0;
        for (int i = 0; i < digit.size(); i++) {
            if (i < a.digit.size()) {   // don't access off the end of the vector!
                tempDiff = digit[i] - a.digit[i] + borrowDigit;
            } else {
                tempDiff = digit[i] + borrowDigit;
            }
            if (tempDiff < 0) {
                result.digit.push_back(tempDiff + 10);
                borrowDigit = -1;
            } else {
                result.digit.push_back(tempDiff);
                borrowDigit = 0;
            }
        }
    } else {    // the difference is negative
        int tempDiff;
        int borrowDigit = 0;
        for (int i = 0; i < a.digit.size(); i++) {
            if (i < digit.size()) {     // don't access off the end of the vector!
                tempDiff = a.digit[i] - digit[i] + borrowDigit;
            } else {
                tempDiff = a.digit[i] + borrowDigit;
            }
            if (tempDiff < 0) {
                result.digit.push_back(tempDiff + 10);
                borrowDigit = -1;
            } else {
                result.digit.push_back(tempDiff);
                borrowDigit = 0;
            }
        }
    }
    // remove the redundant zeros
    for (int i = result.digit.size() - 1; i > 0; i--) {
        if (result.digit[i] == 0) {
            result.digit.pop_back();
        } else {
            break;
        }
    }
    return result;
}

BigInt BigInt::operator*(const BigInt &a) {
    BigInt result;
    // for  one multiplicator is 1 or 0, return quickly
    if (digit.size() == 1) {
        if (digit[0] == 0) {
            result.digit.push_back(0);
            return result;
        } else if (digit[0] == 1) {
            result = a;
            return result;
        }
    }
    if (a.digit.size() == 1) {
        if (a.digit[0] == 0) {
            result.digit.push_back(0);
            return result;
        } else if (a.digit[0] == 1) {
            result = *this;
            return result;
        }
    }

    // for common cases
    int n = a.digit.size();
    result.digit.clear();
    result.digit.push_back(0);
    for (int i = 0; i < n; i++) {
        BigInt tempProduct; // for {digit[0]...digit[n]} * a.digit[i]
        int tempSingleDigitProduct = 0; // for digit[j] * a.digit[i]
        int carry = 0;
        for (int j = 0; j < digit.size(); j++) {
            tempSingleDigitProduct = digit[j] * a.digit[i] + carry;
            if (tempSingleDigitProduct >= 10) {
                tempProduct.digit.push_back(tempSingleDigitProduct % 10);
                carry = tempSingleDigitProduct / 10;
            } else {
                tempProduct.digit.push_back(tempSingleDigitProduct);
                carry = 0;
            }
        }
        if (carry > 0) {
            tempProduct.digit.push_back(carry);
        }
        // insert zeros to low-order for 10x, like 123 -> 1230
        for (int k = 0; k < i; k++) {
            if (tempProduct.digit.size() == 1 && tempProduct.digit[0] == 0) {
                continue;   // if tempProduct is 0
            }
            tempProduct.digit.insert(tempProduct.digit.begin(), 0);
        }
        result = result + tempProduct;
    }
    return result;
}

BigInt BigInt::operator/(const BigInt &a) {
    BigInt result;
    if (a.digit.size() == 1 && a.digit[0] == 0) {           // 0 can not be a divisor
        cout << "error: 0 can not be a divisor!" << endl;
        return result;
    } else if (digit.size() == 1 && digit[0] == 0) {        // 0 / n = 0. (n != 0)
        result.digit.clear();
        result.digit.push_back(0);
        return result;
    } else if (a.digit.size() == 1 && a.digit[0] == 1) {    // n / 1 = n.
        result = *this;
        return result;
    } else {    // common cases
        int compareCode = this->compareWith(a); // compare *this with a
        if (compareCode == 1) {                 // *this > a
            vector<int>::const_iterator start = digit.end() - a.digit.size();
            vector<int>::const_iterator end = digit.end();
            vector<int> tempDividendVec(start, end);
            BigInt tempDividend(tempDividendVec);
            for (int i = digit.size()-a.digit.size(); i >= 0; i--) {    // digit[i]
                if (i != digit.size()-a.digit.size()) {
                    tempDividend = tempDividend * BigInt("10");
                    vector<int> v;
                    v.push_back(digit[i]);
                    tempDividend = tempDividend + BigInt(v);
                }
                compareCode = tempDividend.compareWith(a);
                if (compareCode == 1) {         // tempDividend > a
                    int tempQuotient = 0;
                    while (tempDividend.compareWith(a) == 1 || tempDividend.compareWith(a) == 0) {
                        tempDividend = tempDividend - a;
                        tempQuotient++;
                    }
                    result.digit.push_back(tempQuotient);
                } else if (compareCode == 0) {  // tempDividend == a
                    result.digit.push_back(1);
                    tempDividend = BigInt("0");
                } else if (compareCode == -1) { // tempDividend < a
                    if (result.digit.size() != 0) { // 0 can't be put on high-order
                        result.digit.push_back(0);
                    }
                    continue;
                } else {
                    cout << "error: unexpected return when compare to BigInt." << endl;
                    exit(-1);
                }
            }
        } else if (compareCode == 0) {          // *this == a
            result.digit.clear();
            result.digit.push_back(1);
        } else if (compareCode == -1) {         // *this < a
            result.digit.clear();
            result.digit.push_back(0);
        } else {
            cout << "error: unexpected return when compare to BigInt." << endl;
            exit(-1);
        }
        reverse(result.digit.begin(), result.digit.end());  // reverse result.digit
        return result;
    }
}

int BigInt::compareWith(const BigInt &a) {
    if (digit.size() > a.digit.size()) {
        return 1;
    } else if (digit.size() < a.digit.size()) {
        return -1;
    } else {    // same length
        for (int i = digit.size() - 1; i >= 0; i--) {
            if (digit[i] > a.digit[i]) {
                return 1;
                break;
            } else if (digit[i] < a.digit[i]) {
                return -1;
                break;
            } else {
                if (i == 0) {   // equal
                    return 0;
                } else {
                    continue;
                }
            }
        }
        exit(-1);
    }
}

ostream &operator<<(ostream &os, const BigInt &bi) {
    if (!bi.sign) {   // if bi is a negative number, print minus sign first
        os << "-";
    }
    for (int i = bi.digit.size() - 1; i >= 0; i--) {
        os << bi.digit[i];
    }
    return os;
}

istream &operator>>(istream &is, BigInt &bi) {
    string s;
    cin >> s;
    bi.digit.clear();
    bi = BigInt(s);
    return is;
}

int main(int argc, char const *argv[]) {
    BigInt a;
    char o;
    BigInt b;
    cin >> a;
    cin >> o;
    cin >> b;

    BigInt c;
    switch (o) {
        case '+':
            c = a + b;
            break;
        case '-':
            c = a - b;
            break;
        case '*':
            c = a * b;
            break;
        case '/':
            c = a / b;
            break;
        default:
            cout << "error: unexpected opertor!" << endl;
            exit(-1);
    }
    cout << c << endl;
    return 0;
}
