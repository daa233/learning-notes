/**
 * 期末考试 编程题＃5：走出迷宫（Time Limit Exceeded）
 *
 * @file: GetOutOfMaze.cpp
 * @description: 当你站在一个迷宫里的时候，往往会被错综复杂的道路弄得失去方向感，如果你能得到迷宫地图，事情就会变得
                非常简单。假设你已经得到了一个 n * m 的迷宫的图纸，请你找出从起点到出口的最短路。
 * @input: 第一行是两个整数 n 和 m (1 <= n, m <= 100)，表示迷宫的行数和列数。接下来 n 行，每行一个长为 m 的字
        符串，表示整个迷宫的布局。字符'.'表示空地，'#'表示墙，'S'表示起点,'T'表示出口。
 * @output: 输出从起点到出口最少需要走的步数。(你不能超出迷宫外)
 * @sample_input:
    3 3
    S#T
    .#.
    ...
 * @sample_output:
    6
 *
 * @author: Du Ang
 * @date: Aug. 10th, 2017
 */

#include <iostream>

using namespace std;

struct position {
    int x;
    int y;
};

int takeThisWay(const char maze[100][100], int n, int m, int steps);
bool canMoveOneStep(char maze[100][100], int n, int m, char direction);
position getPosition(char maze[100][100], int n, int m, char c);

void printMaze(char maze[100][100], int n, int m)
{
    cout << "Current maze: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

int takeThisWay(const char maze[100][100], int n, int m, int steps)
{
    // cout << "Enter function takeThisWay..." << endl;
    char tempMaze[100][100];
    // Copy maze to tempMaze
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tempMaze[i][j] = maze[i][j];
        }
    }

    if (steps == -1) {
        // Can not take this way
        // cout << "Exit function takeThisWay..." << endl;
        return -1;
    } else {
        position s = getPosition(tempMaze, n, m, 'S');
        position t = getPosition(tempMaze, n, m, 'T');
        // cout << "S's position: maze[" << s.x << ", " << s.y << "]" << endl;
        // cout << "T's position: maze[" << t.x << ", " << t.y << "]" << endl;

        int distance = (t.x - s.x) + (t.y - s.y);
        // cout << "Distance between S and T: " << distance << endl;
        if ((s.x == t.x || s.y == t.y) && ((distance == 1) || (distance == -1))) {
            // if T is S's neighbor, just take the last step
            // cout << "Exit function takeThisWay..." << endl;
            return (steps + 1);
        } else {
            // T is not S's neighbor, return the steps of the nearest way
            int directionSteps[4] = {0};
            char direction[4] = {'u', 'd', 'l', 'r'};   // up, down, left, right
            for (int i = 0; i < 4; i++) {
                // Refresh the tempMaze
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        tempMaze[i][j] = maze[i][j];
                    }
                }
                if (canMoveOneStep(tempMaze, n, m, direction[i])) {
                    directionSteps[i] = takeThisWay(tempMaze, n, m, steps + 1);
                    // cout << "Steps left in this way: " << directionSteps[i] << endl;
                } else {
                    // Can not take this direction
                    directionSteps[i] = -1;
                }
            }

            int min = -1;
            int hasInitialized = false;

            for (int i = 0; i < 4; i++) {
                if (directionSteps[i] > 0) {
                    if (!hasInitialized) {
                        min = directionSteps[i];
                        hasInitialized = true;
                    } else {
                        if (min > directionSteps[i]) {
                            min = directionSteps[i];
                        }
                    }
                }
            }
            // cout << "Exit function takeThisWay..." << endl;
            return min;
        }
    }
}

/*
 * Given the position of 'S' and the move direction.
 * If we can move, change the maze to status after
 * moving. Replace the old posotion of 'S' with '#'. (Don't go the way we have went before.)
 * If we can't move, return -1.
 */
bool canMoveOneStep(char maze[100][100], int n, int m, char direction)
{
    // cout << "Enter function canMoveOneStep..." << endl;
    position s = getPosition(maze, n, m, 'S');
    // printMaze(maze, n, m);
    // cout << "S's position: maze[" << s.x << ", " << s.y << "]" << endl;
    // cout << "direction: " << direction << endl;
    bool flag = false;
    switch (direction) {
        case 'u':
            if (s.x - 1 < 0) {
                flag = false;
            } else if (maze[s.x - 1][s.y] == '#') {
                flag = false;
            } else if (maze[s.x - 1][s.y] == '.'){
                maze[s.x][s.y] = '#';
                maze[s.x - 1][s.y] = 'S';
                flag = true;
            } else {
                // cout << "Error -1 in direction u" << endl;
                // cout << "Exit function canMoveOneStep..." << endl;
                exit(-1);
            }
            break;
        case 'd':
            if (s.x + 1 >= n) {
                flag = false;
            } else if (maze[s.x + 1][s.y] == '#') {
                flag = false;
            } else if (maze[s.x + 1][s.y] == '.') {
                maze[s.x][s.y] = '#';
                maze[s.x + 1][s.y] = 'S';
                flag = true;
            } else {
                // cout << "Error -1 in direction d" << endl;
                // cout << "Exit function canMoveOneStep..." << endl;
                exit(-1);
            }
            break;
        case 'l':
            if (s.y - 1 < 0) {
                flag = false;
            } else if (maze[s.x][s.y - 1] == '#') {
                flag = false;
            } else if (maze[s.x][s.y - 1] == '.') {
                maze[s.x][s.y] = '#';
                maze[s.x][s.y - 1] = 'S';
                flag = true;
            } else {
                // cout << "Error -1 in direction l" << endl;
                // cout << "Exit function canMoveOneStep..." << endl;
                exit(-1);
            }
            break;
        case 'r':
            if (s.y + 1 >= m) {
                flag = false;
            } else if (maze[s.x][s.y + 1] == '#') {
                flag = false;
            } else if (maze[s.x][s.y + 1] == '.') {
                maze[s.x][s.y] = '#';
                maze[s.x][s.y + 1] = 'S';
                flag = true;
            } else {
                // cout << "Error -1 in direction r" << endl;
                // cout << "Exit function canMoveOneStep..." << endl;
                exit(-1);
            }
            break;
        default:
            // cout << "Error -1 in default" << endl;
            // cout << "Exit function canMoveOneStep..." << endl;
            exit(-1);
    }
    /*
    if (flag) {
        cout << "Can move this direction" << endl;
    } else {
        cout << "Can not move this direction" << endl;
    }
    cout << "Exit function canMoveOneStep..." << endl;
    */
    return flag;
}

// Get the position of 'S' or 'T'
position getPosition(char maze[100][100], int n, int m, char c)
{
    position p = {0, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == c) {
                p.x = i;
                p.y = j;
            }
        }
    }
    return p;
}

int main(int argc, char const *argv[]) {
    int n, m;
    char maze[100][100];
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maze[i][j];
        }
    }
    cout << takeThisWay(maze, n, m, 0) << endl;
    return 0;
}
