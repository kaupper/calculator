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

class NumberExpression {
private:
	static map<string, double (*)(double)> functions;

	static const vector<vector<char>> leftOps;
	static const vector<vector<char>> rightOps;
	static const vector<string> expressionOps;

	static double resolveValue(NumberExpression);


	vector<NumberExpression> numbers;
	vector<string> operations;
	string value;

	string expression;

	bool errorFlag;
	string error;

public:
	NumberExpression() : errorFlag(false), error(""), expression(""), value("") {}
	void process();
	void parse();

	void setValue(string v) { value = v; }
	string getValue() { return value; }

	string getExpression() { return expression; }
	void setExpression(string expr) { expression = expr; } 
};

struct ExpressionParsingResult {
	string lhs;
	string rhs;
	string operation;
};

struct DataStore {
	map<string, double> variables;
	map<string, pair<string, string>> functions;
};


// declare shared variables
extern DataStore store;


// function declarations
double calculate(string);
// ExpressionParsingResult parseExpression(string);



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
