#include "monomial.h"

monomial::monomial(double _coefficient = 0, int _exponent = 0) : coefficient(_coefficient), exponent(_exponent) {}

monomial &monomial::operator=(const monomial &m) {
    if (this == &m)
        return *this;
    this->coefficient = m.coefficient;
    this->exponent = m.exponent;
    return *this;
}