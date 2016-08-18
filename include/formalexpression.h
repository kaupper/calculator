#ifndef FORMALEXPRESSION_H
#define FORMALEXPRESSION_H

#include "calculator.h"

class FormalExpression {
private:
	static const vector<string> expressionOps;

	LeftHandSide lhs;
	RightHandSide rhs;
	std::string operation;
	
	void _process();
	void _parse();
	double _resolveValue();	
	
public:
	FormalExpression() : FormalExpression("") { }
	FormalExpression(std::string exp) : Expression(exp) { }
};

#endif