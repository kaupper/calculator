#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>


// function declarations
double calculate(std::string);


// utils
#define FUNC(n, x) [](double n) {x}
#define DEF_FUNC(name, body) std::make_pair(name, FUNC(n, body))

constexpr long double PI = 3.141592653589793238L;


#include "expression.h"
#include "numberexpression.h"
#include "formalexpression.h"

#endif
