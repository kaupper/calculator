/*
 * process.cpp
 * Copyright (C) 2016 sebastian <sebastian@ARCH-LINUX>
 *
 * Distributed under terms of the MIT license.
 */

#include "calculator.h"

static double doCalculation(double num1, double num2, char op) {
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
	return 0;
}


double process(CalculationParsingResult parsedInput)
{
	vector<double>& numbers = parsedInput.numbers;
	vector<string>& operations = parsedInput.operations;

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
					cout << "do: " << numbers[i] << operations[i] << numbers[i + 1];
#endif
					numbers[i] = doCalculation(numbers[i], numbers[i + 1], operations[i][0]);
					if(errorFlag) {
						return 0;
					}
#ifdef DEBUG
					cout << "=" << numbers[i] << endl;
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
							cout << "do: " << operations[i] << "(" << numbers[i] << ")";
#endif
							numbers[i] = functions[operations[i]](numbers[i]);
#ifdef DEBUG
							cout << "=" << numbers[i] << endl;
#endif

							operations.erase(operations.begin() + i);
							i--;
						} else {
							stringstream ss;
							ss << "unknown function: " << operations[i];
							error = ss.str();
							errorFlag = true;
							return 0;
						}
					}
				} else if(precedence >= 2) {
					// process * and /, + and - calls
					if(operations[i].size() == 1 && find(leftOps[precedence], operations[i][0])) {
#ifdef DEBUG
						cout << "do: " << numbers[i] << operations[i] << numbers[i + 1];
#endif
						numbers[i] = doCalculation(numbers[i], numbers[i + 1], operations[i][0]);

						if (errorFlag) {
							return 0;
						}
#ifdef DEBUG
						cout << "=" << numbers[i] << endl;
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
	return numbers[0];
}



