/**
 * @file: LinkedList.cpp
 * @description: 链表的创建和操作
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 9th, 2017
 */

#include <iostream>

using namespace std;

struct student {
    int num;
    student *next;
};

// Create a linked list
student *create()
{
    student *head, *temp;
    int num, n = 0;
    head = new student;
    temp = head;
    cin >> num;
    while (num != -1) {
        n++;
        temp->num = num;
        temp->next = new student;
        temp = temp->next;
        cin >> num;
    }
    if (n == 0) {
        head = NULL;
    } else {
        temp->next = NULL;
    }
    return head;
}

// Traverse the linked list
void traverse(student *pointer)
{
    while (pointer->next != NULL) {
        cout << pointer->num;
        pointer = pointer->next;
        if (pointer->next == NULL) {
            cout << endl;
        } else {
            cout << " -> ";
        }
    }
}

// Delete the node whose values are n (there is only one in the linked list)
student *del(student *head, int n)
{
    student *temp, *follow;
    temp = head;
    // the linked list is empty
    if (head == NULL) {
        return head;
    }
    // the first node's value is n, delete the first node
    if (head->num == n) {
        head = head->next;
        delete temp;
        return head;
    }
    // look for the target
    while (temp != NULL && temp->num != n) {
        follow = temp;
        temp = temp->next;
    }
    // no target
    if (temp == NULL) {
        cout << "Not found." << endl;
    } else {
        // delete the target node
        follow->next = temp->next;
        delete temp;
    }
    return head;
}

// Insert a node of value n by size up order.
student *insert(student *head, int n)
{
    student *temp, *unit, *follow;
    temp = head;
    unit = new student;
    unit->num = n;
    unit->next = NULL;
    // the linked list is empty, insert directly
    if (head == NULL) {
        head = unit;
        return head;
    }
    while ((temp->next != NULL) && (temp->num < n)) {
        follow = temp;
        temp = temp->next;
    }
    if (temp == head) {
        unit->next = head;
        head = unit;
    } else {
        if (temp->next == NULL) {
            temp->next = unit;
        } else {
            follow->next = unit;
            unit->next = temp;
        }
    }
    return head;
}

int main(int argc, char const *argv[]) {
    // Create a linked list
    cout << "Input nums to create a linked list (-1 to end input): " << endl;
    student *pointer = create();

    // Traverse the linked list
    cout << "The linked list you created is: " << endl;
    traverse(pointer);

    // Delete the one node in some value
    cout << "Input the value of the node that you want to delete: ";
    int target;
    cin >> target;
    pointer = del(pointer, target);
    cout << "The linked list after delete the node in value " << target << ": " << endl;
    traverse(pointer);

    // Insert a node in value target to linked list. Put it after the first node it is larger than
    cout << "Input the value of one node that you want to add: ";
    cin >> target;
    pointer = insert(pointer, target);
    cout << "The linked list after add the node in value " << target << ": " << endl;
    traverse(pointer);
    return 0;
}
