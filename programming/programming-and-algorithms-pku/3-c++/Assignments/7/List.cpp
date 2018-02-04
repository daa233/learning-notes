/**
 *  标准模板库 STL-1 编程题＃2
 *
 * @file: List.cpp
 * @description: 写一个程序完成以下命令：
                new id —— 新建一个指定编号为id的序列(id < 10000)
                add id num —— 向编号为 id 的序列加入整数 num
                merge id1 id2 —— 合并序列 id1 和 id2 中的数，并将 id2 清空
                unique id —— 去掉序列 id 中重复的元素
                out id —— 从小到大输出编号为 id 的序列中的元素，以空格隔开
 * @input: 第一行一个数 n，表示有多少个命令(n <= 200000)。以后 n 行每行一个命令。
 * @output: 按题目要求输出
 * @sample_input:
    16
    new 1
    new 2
    add 1 1
    add 1 2
    add 1 3
    add 2 1
    add 2 2
    add 2 3
    add 2 4
    out 1
    out 2
    merge 1 2
    out 1
    out 2
    unique 1
    out 1
 * @sample_output:
    1 2 3
    1 2 3 4
    1 1 2 2 3 3 4

    1 2 3 4
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <list>
#include <map>

using namespace std;

void createList(map<int, list<int> > &m, int id) {
    m[id] = list<int>();
}

void addNum(map<int, list<int> > &m, int id, int num) {
    m[id].push_back(num);
}

void mergeLists(map<int, list<int> > &m, int id1, int id2) {
    m[id1].sort();
    m[id2].sort();
    m[id1].merge(m[id2]);
}

void unique(map<int, list<int> > &m, int id) {
    m[id].sort();   // must do this before unique()
    m[id].unique();
}

void out(map<int, list<int> > &m, int id) {
    /*if (!m[id].empty()) {

    }*/
    m[id].sort();
    list<int>::iterator i;
    for (i = m[id].begin(); i != m[id].end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    map<int, list<int> > m;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "new") {
            int id;
            cin >> id;
            createList(m, id);
        } else if (cmd == "add") {
            int id, num;
            cin >> id >> num;
            addNum(m, id, num);
        } else if (cmd == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            mergeLists(m, id1, id2);
        } else if (cmd == "unique") {
            int id;
            cin >> id;
            unique(m, id);
        } else if (cmd == "out") {
            int id;
            cin >> id;
            out(m, id);
        } else {
            cerr << "error: unexpected command" << endl;
            exit(-1);
        }
    }
    return 0;
}
