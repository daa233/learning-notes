/**
 *  结构体与链表课堂例题 编程题 #1：约瑟夫问题 No.2
 *
 * @file: JosephusProblem.cpp
 * @description: n 个小孩围坐成一圈，并按顺时针编号为 1, 2, …, n，从编号为 p 的小孩顺时针依次报数，由 1 报到 m，
                当报到 m 时，该小孩从圈中出去，然后下一个再从 1 报数，当报到 m 时再出去。如此反复，直至所有的小孩
                都从圈中出去。请按出去的先后顺序输出小孩的编号。
 * @input: 每行是用空格分开的三个整数，第一个是 n,第二个是 p,第三个是 m (0 < m, n < 300)。最后一行是: 0 0 0
 * @output: 按出圈的顺序输出编号，编号之间以逗号间隔。
 * 样例输入
    8 3 4
    0 0 0
 * 样例输出
    6,2,7,4,3,5,1,8
 *
 * @author: Du Ang
 * @date: Aug. 9th, 2017
 */

#include <iostream>

using namespace std;

struct node {
    int num;
    node *next;
};

// Create the singly linked list, note that the number is from 1 to n, starts at the p-th.
node *create(int n, int p)
{
    // cout << "Start create the linked list in size " << n << " ..." << endl;
    node *head = new node;
    node *temp;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            head->num = i + 1;
            head->next = NULL;
            temp = head;
        } else if (i == n - 1 && n > 1) {
            temp->next = new node;
            temp->next->num = i + 1;
            temp->next->next = head;
        } else {
            temp->next = new node;
            temp->next->num = i + 1;
            temp->next->next = NULL;
            temp = temp->next;
        }
    }
    // cout << "The linked list in size " << n << " has been created." << endl;
    return head;
}

// Traverse and print the linked list. Not necessary for this exercise.
void traverse(node *head)
{
    cout << "The linked list is: ";
    cout << head->num << " -> ";
    node *temp = head->next;
    while (temp != head) {
        cout << temp->num << " -> ";
        temp = temp->next;
    }
    cout << "head" << endl;
}

// Start from the p-th node, delete the m-th node recurrently
void delAndFindLastOne(node *head, int p, int m)
{
    int delNum;
    node *temp = head;
    node *follow;
    // find the p-th node
    while (temp->num != p) {
        follow = temp;
        temp = temp->next;
    }
    while (temp->next != temp) {
        int count = 1;
        // find the m-th node and delete it
        while (count++ != m) {
            follow = temp;
            temp = temp->next;
        }
        // delete the m-th node
        follow->next = temp->next;
        delNum = temp->num;
        cout << delNum << ",";
        delete temp;
        temp = follow->next;
    }
    cout << temp->num << endl;
    delete temp;

}

int main(int argc, char const *argv[]) {
    int n, p, m;
    while (true) {
        cin >> n >> p >> m;
        if (n == 0 && p == 0 && m == 0) {
            break;
        } else {
            node *head;
            head = create(n, p);   // create the linked list
            // traverse(head);
            delAndFindLastOne(head, p, m);
        }
    }
    return 0;
}
