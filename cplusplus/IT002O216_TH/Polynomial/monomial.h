#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class monomial {
public:
    int exponent;
    double coefficient;

    monomial(double _coefficient, int _exponent);

    monomial &operator=(const monomial &m);
};
