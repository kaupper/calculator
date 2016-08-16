/*
 * process.cpp
 * Copyright (C) 2016 sebastian <sebastian@ARCH-LINUX>
 *
 * Distributed under terms of the MIT license.
 */

#include "calculator.h"


double NumberExpression::resolveValue(NumberExpression exp)
{
	return 0.0;
}


static string doCalculation(string num1, string num2, char op) {
	/*
	errorFlag = false;
	switch(op) {
		case '*': return num1 * num2;
		case '/': return num1 / num2;
		case '+': return num1 + num2;
		case '-': return num1 - num2;
		case '^': return pow(num1, num2);
	}
	stringstream ss;
	ss << "unknown operator: " << op;
	error = ss.str();
	errorFlag = true;
	*/
	return "";
}


void NumberExpression::process()
{
	if (value != "") {
		return;
	}

	for(NumberExpression exp : numbers) {
		exp.process();
	}

	// precedences:
	// 0: functions
	// 1: ^
	// 2: * /
	// 3: + -
	for(int precedence = 0; precedence < 4; precedence++) {
		if(precedence == 1) {
			// process pow calls (sqrt calls are functions)
			for(int i = operations.size() - 1; i >= 0; i--) {
				if(operations[i].size() == 1 && find(rightOps[precedence], operations[i][0])) {
#ifdef DEBUG
					cout << "do: " << numbers[i].getValue() << operations[i] << numbers[i + 1].getValue();
#endif
					NumberExpression exp;
					exp.setValue(doCalculation(numbers[i].getValue(), numbers[i + 1].getValue(), operations[i][0]));
					numbers[i] = exp;

					if(errorFlag) {
						return;
					}
#ifdef DEBUG
					cout << "=" << numbers[i].getValue() << endl;
#endif

					numbers.erase(numbers.begin() + i + 1);
					operations.erase(operations.begin() + i);
				}
			}
		} else {
			for(int i = 0; i < operations.size(); i++) {
				if(precedence == 0) {
					// process function calls
					if(operations[i].size() > 1) {
						if(find(functions, operations[i])) {
#ifdef DEBUG
							cout << "do: " << operations[i] << "(" << numbers[i].getValue() << ")";
#endif
							NumberExpression exp;
							exp.setValue(string(functions[operations[i]](resolveValue(numbers[i]))));
							numbers[i] = exp;
#ifdef DEBUG
							cout << "=" << numbers[i].getValue() << endl;
#endif

							operations.erase(operations.begin() + i);
							i--;
						} else {
							stringstream ss;
							ss << "unknown function: " << operations[i];
							error = ss.str();
							errorFlag = true;
							return;
						}
					}
				} else if(precedence >= 2) {
					// process * and /, + and - calls
					if(operations[i].size() == 1 && find(leftOps[precedence], operations[i][0])) {
#ifdef DEBUG
						cout << "do: " << numbers[i].getValue() << operations[i] << numbers[i + 1].getValue();
#endif
						NumberExpression exp;
						exp.setValue(doCalculation(numbers[i].getValue(), numbers[i + 1].getValue(), operations[i][0]));
						numbers[i] = exp;

						if (errorFlag) {
							return;
						}
#ifdef DEBUG
						cout << "=" << numbers[i].getValue() << endl;
#endif

						numbers.erase(numbers.begin() + i + 1);
						operations.erase(operations.begin() + i);
						i--;
					}
				}
			}
		}
	}

#ifdef DEBUG
	cout << endl;
#endif
	errorFlag = false;
}



