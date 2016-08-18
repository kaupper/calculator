#include "formalexpression.h"
#include "calculator.h"

const vector<string> FormalExpression::expressionOps = {":=", "="};

double FormalExpression::resolveValue(FormalExpression& expression) 
{
	if(errorFlag) {
		return;
	}
	
	return 0.0;
}

void FormalExpression::parse()
{
	if(errorFlag) {
		return;
	}
	
	if(parsed) {
		return;
	}
	
}