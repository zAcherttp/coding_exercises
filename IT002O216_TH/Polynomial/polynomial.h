#pragma once
#include "monomial.h"

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

class polynomial
{
public:
    Node *head;
    Node *tail;
    polynomial();

    void insert(double &coefficient, int &exponent);

    friend ostream &operator<<(ostream &os, const polynomial &p);
    friend istream &operator>>(istream &is, polynomial &p);

    void operator=(const polynomial &p);
    polynomial operator+(const polynomial &B);
    polynomial operator-(const polynomial &B);
};



