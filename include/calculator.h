#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;

struct CalculationParsingResult {
	vector<double> numbers;
	vector<string> operations;
};

struct ExpressionParsingResult {
	string lhs;
	string rhs;
	string operation;
};


// declare shared variables
typedef double (*function)(double number);
extern map<string, function> functions; 
extern const vector<vector<char>> rightOps;
extern const vector<vector<char>> leftOps; 
extern const vector<string> expressionOps;
extern bool errorFlag;
extern string error;


// function declarations
double calculate(string);
ExpressionParsingResult parse(string);
CalculationParsingResult parseCalculation(string);
double process(CalculationParsingResult);



// utils

#define FUNC(n, x) [](double n) {x}
#define DEF_FUNC(name, body) make_pair(name, FUNC(n, body))

const long double PI = 3.141592653589793238L;

template <class T> bool find(vector<T> v, T i)
{
	return find(v.begin(), v.end(), i) != v.end();
}

template <class T> bool find(vector<vector<T>> v, T i)
{
	for(auto iv : v) {
		if(find(iv, i)) {
			return true;
		}
	}
	return false;
}

template <class T, class U> bool find(map<T, U> m, T k)
{
	return m.find(k) != m.end();
}

#endif
