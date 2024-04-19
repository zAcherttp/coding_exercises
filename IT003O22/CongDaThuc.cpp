#include <bits/stdc++.h>
using namespace std;

struct monomial
{
    int exponent;
    double coefficient;

    monomial(double _coefficient = 0, int _exponent = 0) : coefficient(_coefficient), exponent(_exponent) {}

    monomial &operator=(const monomial &m)
    {
        if (this == &m)
            return *this;
        this->coefficient = m.coefficient;
        this->exponent = m.exponent;
        return *this;
    }
};

struct Node
{
    monomial *data;
    Node *next;

    Node(monomial *_data = nullptr)
    {
        this->data = _data;
        this->next = nullptr;
    }
};

struct polynomial
{
    Node *head;
    Node *tail;
    polynomial()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void operator=(const polynomial &p)
    {
        Node *current = p.head;
        while (current != nullptr)
        {
            monomial *_monomial = new monomial(current->data->coefficient, current->data->exponent);
            Node *node = new Node(_monomial);
            if (!this->head)
            {
                this->head = node;
                this->tail = node;
            }
            else
            {
                this->tail->next = node;
                this->tail = node;
            }
            current = current->next;
        }
    }
};

void print(polynomial &B)
{
    Node *current = B.head;
    bool isFirst = true;
    while (current != nullptr)
    {
        if (current->data->coefficient != 0)
        {
            if (!isFirst && current->data->coefficient > 0)
                cout << "+";

            if (current->data->coefficient != 1 && current->data->coefficient != -1 && current->data->exponent != 0)
                cout << current->data->coefficient;

            if (current->data->coefficient == -1 && current->data->exponent != 0)
                cout << "-";

            if (current->data->exponent != 0)
                cout << "x";

            if (current->data->exponent != 1 && current->data->exponent != 0)
                cout << "^" << current->data->exponent;

            if (current->data->exponent == 0)
                cout << current->data->coefficient;

            if (isFirst)
                isFirst = false;
        }

        current = current->next;
    }
    if (isFirst)
        cout << "0";
}

void input(polynomial &B, double &coefficient, int &exponent)
{
    monomial *_monomial = new monomial(coefficient, exponent);
    Node *node = new Node(_monomial);
    if (!B.head)
    {
        B.head = node;
        B.tail = node;
    }
    else
    {
        B.tail->next = node;
        B.tail = node;
    }
}

double calc(polynomial B, double x)
{
    double sum = 0.0;
    Node *current = B.head;

    while (current != nullptr)
    {
        sum += current->data->coefficient * pow(x, current->data->exponent);
        current = current->next;
    }

    return sum;
}

polynomial add(polynomial &A, polynomial &B)
{
    polynomial C; // Resultant polynomial

    // Iterate through both lists simultaneously
    Node *currA = A.head, *currB = B.head;
    while (currA != nullptr || currB != nullptr)
    {
        // Create a new node for the result
        Node *newNode = new Node();

        // Case 1: One list is exhausted
        if (currA == nullptr)
        {
            newNode->data = new monomial(*currB->data); // Copy monomial from B
            currB = currB->next;
        }
        else if (currB == nullptr)
        {
            newNode->data = new monomial(*currA->data); // Copy monomial from A
            currA = currA->next;
        }
        else
        {
            // Case 2: Both lists have elements

            // Compare exponents
            if (currA->data->exponent > currB->data->exponent)
            {
                newNode->data = new monomial(*currA->data); // Copy monomial from A
                currA = currA->next;
            }
            else if (currA->data->exponent < currB->data->exponent)
            {
                newNode->data = new monomial(*currB->data); // Copy monomial from B
                currB = currB->next;
            }
            else
            {
                // Case 3: Same exponents, add coefficients
                double new_coeff = currA->data->coefficient + currB->data->coefficient;
                if (new_coeff != 0)
                { // Only add non-zero coefficients
                    newNode->data = new monomial(new_coeff, currA->data->exponent);
                }
                currA = currA->next;
                currB = currB->next;
            }
        }

        // Add the new node to the result list
        if (C.head == nullptr)
        {
            C.head = newNode;
            C.tail = newNode;
        }
        else
        {
            C.tail->next = newNode;
            C.tail = newNode;
        }
    }

    return C;
}

int main()
{
    polynomial A, B, C;
    int a_size, b_size;
    double coefficient;
    int exponent;

    cin >> a_size;
    for (int i{}; i < a_size; i++)
    {
        cin >> coefficient >> exponent;
        input(A, coefficient, exponent);
    }

    cin >> b_size;
    for (int i{}; i < b_size; i++)
    {
        cin >> coefficient >> exponent;
        input(B, coefficient, exponent);
    }

    cout << "Da thuc A: ";
    print(A);
    cout << '\n';
    cout << "Da thuc B: ";
    print(B);
    cout << '\n';
    cout << "A+B = ";
    C = add(A, B);
    print(C);
    cout << '\n';
    cout << calc(C, 10);
    return 0;
}
