#ifndef EXPRESSION_HAND_SIDE_H
#define EXPRESSION_HAND_SIDE_H

#include "calculator.h"

class Expression {
private:
	bool errorFlag;
	std::string error;
	
	std::string expression;
	bool parsed;
	bool processed;
	bool resolved;
	
	std::string stringValue;
	double doubleValue;
	
	
	virtual void _parse() = 0;
	virtual void _process() = 0;
	virtual double _resolveValue() = 0;

public:
	Expression() : Expression("") {}
	Expression(std::string exp) : 
		errorFlag(false), 
		error(""), 
		expression(exp), 
		parsed(false), 
		processed(false), 
		resolved(false),
		stringValue(""),
		doubleValue(0.0){}

	void parse();
	void process();
	double resolveValue();

	std::string getExpression() { return expression; }
	void setExpression(std::string exp) { expression = exp; }

	std::string getStringValue() { return stringValue; }
	void setStringValue(std::string v) { stringValue = v;}
	
	double getDoubleValue() { return doubleValue; }
	void setDoubleValue(double v) { doubleValue = v; }
	
	bool isParsed() { return parsed; }
	
	std::string getError() { return error; }
	bool hasError() { return errorFlag; }
	
	void resetError() { errorFlag = false; }
};


#endif