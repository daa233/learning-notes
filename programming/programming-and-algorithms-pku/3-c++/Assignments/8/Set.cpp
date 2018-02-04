/**
 *  标准模板库 STL-2 编程题＃3 Set
 *
 * @file: Set.cpp
 * @description:
    现有一整数集（允许有重复元素），初始为空。我们定义如下操作：
    add x 把 x 加入集合
    del x 把集合中所有与 x 相等的元素删除
    ask x 对集合中元素 x 的情况询问

    对每种操作，我们要求进行如下输出。
    add 输出操作后集合中 x 的个数
    del 输出操作前集合中 x 的个数
    ask 先输出 0 或 1 表示 x 是否曾被加入集合（0 表示不曾加入），再输出当前集合中 x 的个数，中间用空格格开。
 * @input: 第一行是一个整数 n，表示命令数。0 <= n <= 100000。后面 n 行命令，如 description 中所述。
 * @output: 共n行，每行按要求输出。
 * @sample_input:
    7
    add 1
    add 1
    ask 1
    ask 2
    del 2
    del 1
    ask 1
 * @sample_output:
    1
    2
    1 2
    0 0
    0
    2
    1 0
 * @hint: Please use STL’s set and multiset to finish the task
 *
 * @author: Du Ang
 * @date: Aug. 31st, 2017
 */

#include <iostream>
#include <set>

using namespace std;

void add(multiset<int> &st, int num) {
    st.insert(num);
    cout << st.count(num) << endl;
}

void del(multiset<int> &st, int num) {
    cout << st.count(num) << endl;
    st.erase(num);
}

void ask(multiset<int> &st, set<int> &memory, int num) {
    int count = st.count(num);
    bool hasBeenStoredBefore;
    if (memory.find(num) == memory.end()) {
        hasBeenStoredBefore = false;
    } else {
        hasBeenStoredBefore = true;
    }
    cout << hasBeenStoredBefore << " " << count << endl;
}

int main(int argc, char const *argv[]) {
    int n;
    multiset<int> st;
    set<int> memorySet;
    cin >> n;
    while (n--) {
        string cmd;
        int x;
        cin >> cmd;
        cin >> x;
        if (cmd == "add") {
            add(st, x);
            memorySet.insert(x);
        } else if (cmd == "del") {
            del(st, x);
        } else if (cmd == "ask") {
            ask(st, memorySet, x);
        } else {
            cerr << "error: unexpected command" << endl;
            exit(-1);
        }
    }
    return 0;
}
