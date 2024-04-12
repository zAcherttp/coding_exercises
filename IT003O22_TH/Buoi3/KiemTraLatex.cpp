// dung stack de kiem tra {[()]}
#include <iostream>
#include <stack>
#include <string.h>

using namespace std;

int main()
{
    string input;
    stack<char> stack;
    getline(cin, input);
    int output = 1;
    for (char c : input)
    {
        if (c == '{' || c == '[' || c == '(')
        {
            stack.push(c);
        }
        else if (c == '}' || c == ']' || c == ')')
        {
            if (stack.empty())
            {
                output = 0;
            }
            else
            {
                char top = stack.top();
                if ((c == '}' && top == '{') || (c == ']' && top == '[') || (c == ')' && top == '('))
                {
                    stack.pop();
                }
                else
                {
                    output = 0;
                    break;
                }
            }
        }
    }
    if (!stack.empty())
    {
        output = 0;
    }
    std::cout << output;
    return 0;
}