#include "calculator.h"

map<string, function> functions = {
	make_pair("sqrt", 	FUNC(n, return sqrt(n);)),
	make_pair("sin", 	FUNC(n, return sin(n);)),
	make_pair("cos", 	FUNC(n, return cos(n);)),
	make_pair("tan", 	FUNC(n, return tan(n);)),
	make_pair("asin", 	FUNC(n, return asin(n);)),
	make_pair("acos", 	FUNC(n, return acos(n);)),
	make_pair("atan", 	FUNC(n, return atan(n);)),
	make_pair("floor", 	FUNC(n, return floor(n);)),
	make_pair("ceil", 	FUNC(n, return ceil(n);)),
	make_pair("deg", 	FUNC(n, return (double)(n / PI * 180.0);)),
	make_pair("rad",	FUNC(n, return (double)(n / 180.0 * PI);))
};
const vector<vector<char>> rightOps = {{}, {'^'}, {}, {}};
const vector<vector<char>> leftOps = {{}, {}, {'*', '/'}, {'+', '-'}};

const vector<string> expressionOps = {"=", ":="};

bool errorFlag = false;
string error = "";


double calculate(string input)
{
	CalculationParsingResult parsedInput = parseCalculation(input);
	if(errorFlag) {
		return 0;
	}
	
	double result = process(parsedInput);
	if(errorFlag) {
		return 0;
	}

	errorFlag = false;
	return result;
}
