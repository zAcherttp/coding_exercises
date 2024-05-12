#include <iostream>
#include <limits>
using namespace std;

class SinglyLinkedListNode {
public:
    int data;
    SinglyLinkedListNode *next;

    SinglyLinkedListNode(int node_data) {
        this->data = node_data;
        this->next = nullptr;
    }
};

class SinglyLinkedList {
public:
    SinglyLinkedListNode *head;
    SinglyLinkedListNode *tail;

    SinglyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }
};

// Complete the insertSortedLinkedList function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

void insert_node(SinglyLinkedList *llist, int item) {
    SinglyLinkedListNode *node = new SinglyLinkedListNode(item);
    node->next = llist->head;
    llist->head = node;
}

void reverseLinkedList(SinglyLinkedList *llist) {
    SinglyLinkedListNode *current = llist->head;

    int size = 0, i = 0;
    while (current != nullptr) {
        size++;
        current = current->next;
    }

    current = llist->head;
    int data[size];
    while (current != nullptr) {
        data[i++] = current->data;
        current = current->next;
    }

    current = llist->head;
    i = 0;
    while (current != nullptr) {
        current->data = data[i++];
        current = current->next;
    }
}

void printLinkedList(SinglyLinkedList *llist) {
    SinglyLinkedListNode *current = llist->head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
}

int main() {
    SinglyLinkedList *llist = new SinglyLinkedList();
    int llist_count;

    cin >> llist_count;

    for (int i = 0; i < llist_count; i++) {
        int llist_item;
        cin >> llist_item;

        insert_node(llist, llist_item);
    }

    reverseLinkedList(llist);
    printLinkedList(llist);

    return 0;
}