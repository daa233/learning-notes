/**
 * 综合编程练习（2） 编程题＃2：配对碱基链
 *
 * @file: MatchBaseChain.cpp
 * @description: 脱氧核糖核酸（DNA）由两条互补的碱基链以双螺旋的方式结合而成。而构成 DNA 的碱基共有 4 种，分别为腺
                瞟呤（A）、鸟嘌呤（G）、胸腺嘧啶（T）和胞嘧啶（C）。我们知道，在两条互补碱基链的对应位置上，腺瞟呤总
                是和胸腺嘧啶配对，鸟嘌呤总是和胞嘧啶配对。你的任务就是根据一条单链上的碱基序列，给出对应的互补链上的
                碱基序列。
 * @input: 第一行是一个正整数 n，表明共有n条要求解的碱基链。以下共有 n 行，每行用一个字符串表示一条碱基链。这个字符
        串只含有大写字母A、T、G、C，分别表示腺瞟呤、胸腺嘧啶、鸟嘌呤和胞嘧啶。每条碱基链的长度都不超过 255。
 * @output: 共有 n 行，每行为一个只含有大写字母 A、T、G、C 的字符串。分别为与输入的各碱基链互补的碱基链。
 * @sample_input:
    5
    ATATGGATGGTGTTTGGCTCTG
    TCTCCGGTTGATT
    ATATCTTGCGCTCTTGATTCGCATATTCT
    GCGTTTCGTTGCAA
    TTAACGCACAACCTAGACTT
 * @sample_output:
    TATACCTACCACAAACCGAGAC
    AGAGGCCAACTAA
    TATAGAACGCGAGAACTAAGCGTATAAGA
    CGCAAAGCAACGTT
    AATTGCGTGTTGGATCTGAA
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>

using namespace std;

char matchBase(char c)
{
    switch (c) {
        case 'A':
            return 'T';
        case 'T':
            return 'A';
        case 'C':
            return 'G';
        case 'G':
            return 'C';
        default:
            return '\0';
    }
}

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    char c[n][255];

    for (int i = 0; i < n; i++) {
        cin >> c[i];
        int j = 0;
        while (c[i][j] != '\0') {
            cout << matchBase(c[i][j]);
            j++;
        }
        cout << endl;
    }
    return 0;
}
