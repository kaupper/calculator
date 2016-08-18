#include "calculator.h"

DataStore store;

ExpressionParsingResult parseExpression(string input)
{
	return ExpressionParsingResult();
}

double calculate(string input)
{
	NumberExpression expression(input);
	expression.parse();
	return NumberExpression::resolveValue(expression);
}
