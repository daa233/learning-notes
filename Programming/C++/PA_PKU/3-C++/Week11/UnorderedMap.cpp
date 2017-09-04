/**
 * @file: UnorderedMap.cpp
 * @description: C++11 新特性，无序容器（哈希表）
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 4th, 2017
 */

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(int argc, char const *argv[]) {
    unordered_map<string, int> turingWinner;
    turingWinner.insert(make_pair("Dijkstra", 1972));
    turingWinner.insert(make_pair("Scott", 1976));
    turingWinner.insert(make_pair("Wilkes", 1967));
    turingWinner.insert(make_pair("Hanmming", 1968));
    turingWinner["Ritchie"] = 1983;
    string name;
    cin >> name;
    unordered_map<string, int>::iterator p = turingWinner.find(name);
    if (p != turingWinner.end()) {
        cout << p->second << endl;
    } else {
        cout << "Not found" << endl;
    }
    return 0;
}
