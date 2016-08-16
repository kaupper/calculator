#include "calculator.h"

DataStore store;

ExpressionParsingResult parseExpression(string input)
{
	return ExpressionParsingResult();
}

double calculate(string input)
{
	NumberExpression expression;
	expression.setExpression(input);
	expression.parse();
	return 0.0;
}
