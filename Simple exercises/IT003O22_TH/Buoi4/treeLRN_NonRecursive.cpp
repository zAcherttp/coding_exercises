
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    Node *insert(Node *root, int data) {
        if (root == NULL) {
            return new Node(data);
        } else {
            Node *cur;
            if (data <= root->data) {
                cur = insert(root->left, data);
                root->left = cur;
            } else {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    /* you only have to complete the function given below.
    Node is defined as

    class Node {
        public:
            int data;
            Node *left;
            Node *right;
            Node(int d) {
                data = d;
                left = NULL;
                right = NULL;
            }
    };

    */

    void preOrder(Node *root) {
        if (!root)
            return;

        stack<pair<Node *, bool>> stack;
        stack.push({root, false});

        while (!stack.empty()) {
            pair<Node *, bool> cur = stack.top();
            stack.pop();

            Node *curr = cur.first;
            bool visited = cur.second;

            if (!visited) {
                stack.push({curr, true});
                if (curr->right) {
                    stack.push({curr->right, false});
                }
                if (curr->left) {
                    stack.push({curr->left, false});
                }
            } else {
                cout << curr->data << " ";
            }
        }
    }
}; // End of Solution

int main() {

    Solution myTree;
    Node *root = NULL;

    int t;
    int data;

    std::cin >> t;

    while (t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }

    myTree.preOrder(root);

    return 0;
}