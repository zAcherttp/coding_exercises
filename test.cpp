// #include <bits/stdc++.h>
// using namespace std;

// bool compareFiles(const string &outputFilename, const string &pregen_outputFilename)
// {
//     ifstream output(outputFilename);
//     ifstream pregen_output(pregen_outputFilename);

//     if (!output.is_open() || !pregen_output.is_open())
//     {
//         cerr << "Error opening files: " << outputFilename << " or " << outputFilename << endl;
//         return false;
//     }

//     string line1, line2;
//     while (getline(output, line1) && getline(pregen_output, line2))
//     {
//         if (line1 != line2)
//         {
//             cerr << "Mismatch in line: " << output.tellg() + (long long int)2 << endl;
//             return false;
//         }
//     }

//     // Check if any lines are left in either file
//     if (output.eof() != pregen_output.eof())
//     {
//         cerr << "Files have different line count." << endl;
//         return false;
//     }

//     return true;
// }

// class Node
// {
// public:
//     int data;
//     Node *left;
//     Node *right;
//     Node(int d)
//     {
//         data = d;
//         left = NULL;
//         right = NULL;
//     }
// };

// class Solution
// {
// public:
//     Node *insert(Node *root, int data)
//     {
//         if (root == NULL)
//         {
//             return new Node(data);
//         }
//         else
//         {
//             Node *cur;
//             if (data <= root->data)
//             {
//                 cur = insert(root->left, data);
//                 root->left = cur;
//             }
//             else
//             {
//                 cur = insert(root->right, data);
//                 root->right = cur;
//             }

//             return root;
//         }
//     }
//     /*The tree node has data, left child and right child
//     class Node {
//         int data;
//         Node* left;
//         Node* right;
//     };

//     */
//     int height(Node *root)
//     {
//         if (root == nullptr)
//         {
//             return 0;
//         }
//         else
//         {
//             int l_depth = height(root->left);
//             int r_depth = height(root->right);

//             if (l_depth > r_depth)
//                 return l_depth + 1;
//             else
//                 return r_depth + 1;
//         }
//     }

// }; // End of Solution

// int main()
// {
//     int check = 0, cases = 10;
//     for (int i = 1; i <= cases; ++i)
//     {

//         ofstream output("t_output" + to_string(i) + ".txt");
//         ifstream input("input" + to_string(i) + ".txt");

//         Solution myTree;
//         Node *root = NULL;
//         int t;
//         int data;
//         input >> t;
//         while (t-- > 0)
//         {
//             input >> data;
//             root = myTree.insert(root, data);
//         }
//         int height = myTree.height(root);
//         output << height;

//         output.close();
//         input.close();

//         if (compareFiles("t_output" + to_string(i) + ".txt", "output" + to_string(i) + ".txt"))
//         {
//             cout << "Test case " << i << " passed." << endl;
//             check++;
//         }
//         else
//         {
//             cout << "Test case " << i << " failed." << endl;
//         }
//     }
//     cout << check << "/" << cases << " cases passed." << endl;
//     return 0;
// }

#include <iostream>
#define N 100
using namespace std;

int main() {
    char input[N], cmp[N];
    cin.getline(input, N);
    cin.getline(cmp, N);

    char *p1 = input, *p2 = cmp;
    int size1 = 0, size2 = 0;
    while (*p1 != '\0') {
        size1++;
        p1++;
    }
    while (*p2 != '\0') {
        size2++;
        p2++;
    }
    p1 = input, p2 = cmp;

    bool isEqual = true;
    bool firstHalf = false;
    bool lastHalf = false;

    while (lastHalf == false) {
        cout << "checking '" << *p1 << "' and '" << *p2 << "': ";
        if (*p2 == '*') {
            cout << "wildcard!\n";
            if (firstHalf)
                lastHalf = true;
            if (!firstHalf)
                firstHalf = true;

            p1 = input + size1;
            p2 = cmp + size2;
        } else if (*p2 != *p1) {
            cout << "not equal!\n";
            isEqual = false;
            break;
        } else {
            cout << "equal!\n";
        }

        if (!firstHalf) {
            p1++;
            p2++;
        } else {
            p1--;
            p2--;
        }

        if(*p1 == '\0' && *p2 == '\0') {
            isEqual = true;
            break;
        }
    }

    cout << isEqual;
    return 0;
}