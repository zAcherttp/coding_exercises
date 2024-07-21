#include <bits/stdc++.h>
using namespace std;
class LinkedListBTree {
    struct Link {
        int data;
        Link *next;
        Link(int data) {
            this->data = data;
            this->next = nullptr;
        }
    };
    struct Node {
        Link *link;
        Node *left;
        Node *right;
        Node(int data) {
            this->link = new Link(data);
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    Node *root;

public:
    LinkedListBTree() {
        root = nullptr;
    }

    void insert(int data) {
        Link *newLink = new Link(data);
        Node *newNode = new Node(data);

        if (!root) {
            root = new Node(data);
            // cout << "root created!\n";
            return;
        }

        bool inserted = false;
        Node *curr = root;
        while (!inserted) {
            if (curr->link->data < data) {
                if (curr->right) {
                    curr = curr->right;
                    // cout << "moved right!\n";
                } else {
                    curr->right = newNode;
                    inserted = true;
                    // cout << "inserted right!\n";
                    return;
                }
            } else if (curr->link->data > data) {
                if (curr->left) {
                    curr = curr->left;
                    // cout << "moved left!\n";
                } else {
                    curr->left = newNode;
                    inserted = true;
                    // cout << "inserted left!\n";
                    return;
                }
            } else {
                Link *cur = curr->link;
                while (cur->next) {
                    cur = cur->next;
                    // cout << "traversed chain!\n";
                }
                cur->next = newLink;
                inserted = true;
                // cout << "linked at back!\n";
                return;
            }
        }
    }

    void buildTree() {
        int temp;
        cin >> temp;
        while (temp) {
            this->insert(temp);
            cin >> temp;
        }
        return;
    }

    void printTreeAscending() {
        cout << "Tree in ascending order: \n";
        // LNR traversal
        stack<Node *> s;
        Node *cur = this->root;
        while (cur || !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            /////// printing ///////
            Link *curr = cur->link;
            int count = 1;
            while (curr->next) {
                count++;
                curr = curr->next;
            }
            cout << curr->data << " x " << count << endl;
            ////////////////////////
            cur = cur->right;
        }
    }

    void printOddLeaves() {
        cout << "Odd leaves: ";
        // LNR traversal
        stack<Node *> s;
        Node *cur = this->root;
        while (cur || !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            /////// printing ///////
            if (cur->link->data % 2)
                cout << cur->link->data << " ";
            ////////////////////////
            cur = cur->right;
        }
        cout << endl;
    }

    int countAllNodes(Node *root) {
        // LNR traversal
        stack<Node *> s;
        Node *cur = root;
        int count = 0;
        while (cur || !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            /////// counting ///////
            count++;
            ////////////////////////
            cur = cur->right;
        }
        return count;
    }

    void printLeavesOfEqualChildren() {
        vector<int> leaves;
        // LNR traversal
        stack<Node *> s;
        Node *cur = this->root;
        while (cur || !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            /////// checking ///////
            if (this->countAllNodes(cur->left) == this->countAllNodes(cur->right))
                leaves.push_back(cur->link->data);
            ////////////////////////
            cur = cur->right;
        }

        cout << "Leaves of equal children: ";
        for (int i : leaves) {
            cout << i << " ";
        }
        cout << endl;
    }

    void levelLeaves(Node *root, int level, unordered_map<int, int> &counter) {
        // NLR traversal
        if (!root)
            return;
        if (!root->left && !root->right)
            counter[level]++;
        levelLeaves(root->left, level + 1, counter);
        levelLeaves(root->right, level + 1, counter);
    }

    void levelThatHasTheMostLeaves() {
        unordered_map<int, int> check;
        levelLeaves(this->root, 0, check);
        cout << "Level " << max_element(check.begin(), check.end(), [&](pair<int, int> a, pair<int, int> b) { return a.second < b.second; })->first
             << " has the most leaves!" << endl;
        //  lambda function:
        //
        //  [capture](parameters) -> return_type { function };
        //
        // Capture by Value     [=]: Captures all surrounding variables by value.
        // Capture by Reference [&]: Captures all surrounding variables by reference.
        // Capture Specific Variables: You can specify particular variables to capture by value or by reference.
        //     For example:     [x, &y]: Captures x by value and y by reference.
    }
};

int main() {
    LinkedListBTree tree;
    tree.buildTree();

    tree.printTreeAscending();
    tree.printOddLeaves();
    tree.printLeavesOfEqualChildren();
    tree.levelThatHasTheMostLeaves();

    return 0;
}