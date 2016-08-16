/*
 * parse.cpp
 * Copyright (C) 2016 sebastian <sebastian@ARCH-LINUX>
 *
 * Distributed under terms of the MIT license.
 */

#include "calculator.h"

map<string, double (*)(double)> NumberExpression::functions = {
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
const vector<vector<char>> NumberExpression::rightOps = {{}, {'^'}, {}, {}};
const vector<vector<char>> NumberExpression::leftOps = {{}, {}, {'*', '/'}, {'+', '-'}};

const vector<string> NumberExpression::expressionOps = {":=", "="};

void NumberExpression::parse() 
{
	const string& input = expression;
	string number = "";

	int opened = 0;
	int closed = 0;
	int firstOpenedIndex = -1;

	int lastOp = -1;

	string func = "";


	for(int i = 0; i < input.size(); i++) {
		char c = input[i];

		if(c == '(') {
			if(func != "") {
				operations.push_back(func);
				func = "";
			} 	
			if(opened == 0) {
				firstOpenedIndex = i;
			}
			opened++;
			continue;
		} else if(c == ')') {
			closed++;
			if(opened == closed) {
				string innerExpression = input.substr(firstOpenedIndex + 1, i - firstOpenedIndex - 1);
				NumberExpression expression;
				expression.setExpression(innerExpression);
				expression.parse();
				numbers.push_back(expression);

				if(errorFlag) {
					return;
				}
			}
			continue;
		}

		if(opened != closed) {
			continue;
		}

		if(lastOp == i - 1 && c == '-') {
			number = "-" + number;
			continue;
		}

		if(find(leftOps, c) || find(rightOps, c)) {
			NumberExpression expression;
			if(number != "") {
				expression.setValue(number);
			} else if(func != "") {
				expression.setValue(func);
			}
			numbers.push_back(expression);
			operations.push_back(string(1, c));

			func = "";
			number = "";
			lastOp = i;
		} else if(c >= 'a' && c <= 'z') {
			func += c;
		} else if(c == '.' || (c >= '0' && c <= '9')) {
			number += c;
		} else {
			stringstream ss;
			ss << "unknown sign: " << c;
			error = ss.str();
			errorFlag = true;
			return;
		}	
	}

	NumberExpression expression;
	if(number != "") {
		expression.setValue(number);
	} else if(func != "") {
		expression.setValue(func);
	}
	numbers.push_back(expression);

#ifdef DEBUG
	cout << "numbers:" << endl;
	for(NumberExpression n : numbers) {
		cout << n.getValue() << " ";
	}
	cout << endl << "operations:" << endl;
	for(string o : operations) {
		cout << o << " ";
	}
	cout << endl;
#endif

	errorFlag = false;
}


/*
ExpressionParsingResult parseExpression(string input)
{
	ExpressionParsingResult result;
	result.rhs = input;

	for(string operation : expressionOps) {
		int index = 0;
		if((index = input.find(operation)) != string::npos) {
			result.lhs = input.substr(0, index);
			result.operation = input.substr(index, operation.size());
			result.rhs = input.substr(index + operation.size());
			break;
		}
	}

#ifdef DEBUG
	cout << "expression" << endl;
	cout << "lhs      : " << result.lhs << endl;
	cout << "operation: " << result.operation << endl;
	cout << "rhs      : " << result.rhs << endl;
	cout << endl;
#endif

	return result;
}
*/


