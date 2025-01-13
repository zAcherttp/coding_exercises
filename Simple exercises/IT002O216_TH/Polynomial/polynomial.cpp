#include "polynomial.h"

polynomial::polynomial() {
    this->head = nullptr;
    this->tail = nullptr;
}

ostream &operator<<(ostream &os, const polynomial &p) {
    Node *current = p.head;
    bool isFirst = true;
    while (current != nullptr) {
        if (current->data->coefficient != 0) {
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
    return os;
}

void polynomial::insert(double &coefficient, int &exponent) {
    monomial *_monomial = new monomial(coefficient, exponent);
    Node *node = new Node(_monomial);
    if (!this->head) {
        this->head = node;
        this->tail = node;
    } else {
        this->tail->next = node;
        this->tail = node;
    }
}

istream &operator>>(istream &is, polynomial &p) {
    double coefficient;
    int exponent;
    int size;
    cin >> size;
    for (int i{}; i < size; i++) {
        cin >> coefficient >> exponent;
        p.insert(coefficient, exponent);
    }
    return is;
}

void polynomial::operator=(const polynomial &p) {
    Node *current = p.head;
    while (current != nullptr) {
        monomial *_monomial = new monomial(current->data->coefficient, current->data->exponent);
        Node *node = new Node(_monomial);
        if (!this->head) {
            this->head = node;
            this->tail = node;
        } else {
            this->tail->next = node;
            this->tail = node;
        }
        current = current->next;
    }
}

polynomial polynomial::operator+(const polynomial &B) {
    polynomial result;

    Node *currA = this->head;
    Node *currB = B.head;
    while (currA != nullptr || currB != nullptr) {
        if (currA == nullptr) {
            result.insert(currB->data->coefficient, currB->data->exponent);
            currB = currB->next;
        } else if (currB == nullptr) {
            result.insert(currA->data->coefficient, currA->data->exponent);
            currA = currA->next;
        } else {
            if (currA->data->exponent > currB->data->exponent) {
                result.insert(currA->data->coefficient, currA->data->exponent);
                currA = currA->next;
            } else if (currA->data->exponent < currB->data->exponent) {
                result.insert(currB->data->coefficient, currB->data->exponent);
                currB = currB->next;
            } else {
                double new_coeff = currA->data->coefficient + currB->data->coefficient;
                if (new_coeff != 0) {
                    result.insert(new_coeff, currA->data->exponent);
                }
                currA = currA->next;
                currB = currB->next;
            }
        }
    }

    return result;
}

polynomial polynomial::operator-(const polynomial &B) {
    polynomial result;

    Node *currA = this->head;
    Node *currB = B.head;
    while (currA != nullptr || currB != nullptr) {
        if (currA == nullptr) {
            result.insert(currB->data->coefficient, currB->data->exponent);
            currB = currB->next;
        } else if (currB == nullptr) {
            result.insert(currA->data->coefficient, currA->data->exponent);
            currA = currA->next;
        } else {
            if (currA->data->exponent > currB->data->exponent) {
                result.insert(currA->data->coefficient, currA->data->exponent);
                currA = currA->next;
            } else if (currA->data->exponent < currB->data->exponent) {
                result.insert(currB->data->coefficient, currB->data->exponent);
                currB = currB->next;
            } else {
                double new_coeff = currA->data->coefficient - currB->data->coefficient;
                if (new_coeff != 0) {
                    result.insert(new_coeff, currA->data->exponent);
                }
                currA = currA->next;
                currB = currB->next;
            }
        }
    }

    return result;
}