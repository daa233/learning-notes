/**
 * @file: MultiMapExercise.cpp
 * @description: STL 中 multimap 例题
                一个学生成绩录入和查询系统，接受以下两种输入：
                    Add name id score
                    Query score
                其中，name 是个字符串，中间没有空格，代表学生姓名。id 是个整数，代表学号。score 是个整数，表示分
                数。学号不会重复，分数和姓名都可能重复。

                两种输入交替出现。第一种输入表示要添加一个学生的信息，碰到这种输入，就记下学生的姓名、id 和分数。第
                二种输入表示要查询，碰到这种输入，就输出已有记录中分数比 score 低的最高分获得者的姓名、学号和分数。
                如果有多个学生都满足条件，就输出学号最大的那个学生的信息。如果找不到满足条件的学生，则输出“Nobody”

                要求添加和查询学生的成绩的速度都很快。关联容器特别适合用于一些需要不断更新数据和查询数据的情形。
 * @sample_input:
    Add Jack 12 78
    Query 78
    Query 81
    Add Percy 9 81
    Add Marry 8 81
    Query 82
    Add Tom 11 79
    Query 80
    Query 81
 * @output:
    Nobody
    Jack 12 78
    Percy 9 81
    Tom 11 79
    Tom 11 79
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <map>
#include <string>

using namespace std;

class CStudent {
public:
    struct CInfo {  // we can define another class inside a class
        int id;
        string name;
    };
    int score;
    CInfo info;     // the information of a student
};

typedef multimap<int, CStudent::CInfo> MAP_STD;

int main(int argc, char const *argv[]) {
    MAP_STD mp;
    CStudent st;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "Add") {
            cin >> st.info.name >> st.info.id >> st.score;
            // instantiate a pair object, same as 'mp.insert(make_pair(st.score, st.info));'
            // mp.insert(MAP_STD::value_type(st.score, st.info));
            mp.insert(make_pair(st.score, st.info));
        } else if (cmd == "Query") {
            int score;
            cin >> score;
            // iterator lower_bound(const T &val) will find a it, s.t. all the first of
            // elements range in [begin(), it) are smaller than val
            MAP_STD::iterator p = mp.lower_bound(score);
            if (p != mp.begin()) {  // found
                --p;
                score = p->first;
                // find the highest score (lower than query score) with the largest id
                MAP_STD::iterator maxp = p;
                int maxId = p->second.id;
                for ( ; p != mp.begin() && p->first == score; --p) {
                    if (p->second.id > maxId) {
                        maxp = p;
                        maxId = p->second.id;
                    }
                }
                // the for-loop may end with p == mp.begin()
                // if then, check if mp.begin()->first == score
                if (p->first == score) {
                    if (p->second.id > maxId) {
                        maxp = p;
                        maxId = p->second.id;
                    }
                }
                cout << maxp->second.name << " " << maxp->second.id << " " << maxp->first << endl;
            } else {    // not found
                cout << "Nobody" << endl;
            }
        }
    }
    return 0;
}
