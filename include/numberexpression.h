#ifndef NUMBEREXPRESSION_H
#define NUMBEREXPRESSION_H

#include "expression.h"

class NumberExpression : Expression{
private:
	static map<string, double (*)(double)> functions;

	static const vector<vector<char>> leftOps;
	static const vector<vector<char>> rightOps;

	static string doCalculation(NumberExpression&, NumberExpression&, char);
	static string doCalculation(NumberExpression&, string);

	vector<NumberExpression> numbers;
	vector<string> operations;
	
	void _process();
	void _parse();
	double _resolveValue();

public:	
	NumberExpression() : NumberExpression("") {}
	NumberExpression(string exp) : Expression(exp) { }
};

#endif