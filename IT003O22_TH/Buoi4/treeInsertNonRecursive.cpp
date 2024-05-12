
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
    void preOrder(Node *root) {

        if (root == NULL)
            return;

        std::cout << root->data << " ";

        preOrder(root->left);
        preOrder(root->right);
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

    Node *insert(Node *root, int data) {
        Node *x = new Node(data);
        Node *pos = root;
        if (!root) {
            root = x;
            //      cout << x->data << endl;
        } else {
            while (pos) {
                if (data < pos->data) {
                    if (pos->left == nullptr) {
                        pos->left = x;
                        return root;
                    }
                    pos = pos->left;
                } else {
                    if (pos->right == nullptr) {
                        pos->right = x;
                        return root;
                    }
                    pos = pos->right;
                }
                //           cout << root << endl;
            }
            //        cout << x->data << endl;
        }
        return root;
    }
};

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