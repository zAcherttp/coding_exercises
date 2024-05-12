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