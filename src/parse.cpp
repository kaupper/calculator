/*
 * parse.cpp
 * Copyright (C) 2016 sebastian <sebastian@ARCH-LINUX>
 *
 * Distributed under terms of the MIT license.
 */

#include "calculator.h"



ExpressionParsingResult parse(string input)
{
	ExpressionParsingResult result;

	errorFlag = false;
	return result;
}

CalculationParsingResult parseCalculation(string input) 
{
	CalculationParsingResult result;
	vector<double>& numbers = result.numbers;
	vector<string>& operations = result.operations;

	double number = 0;

	bool greaterZero = true;
	int decimalPosition = 1;

	int opened = 0;
	int closed = 0;
	int firstOpenedIndex = -1;

	int numberSign = 1;
	int lastOp = -1;

	string func = "";


	for(int i = 0; i < input.size(); i++) {
		char c = input[i];

		// open bracket.
		if(c == '(') {
			if(func != "") {
				// save function if there was any
				operations.push_back(func);
				func = "";
			} 	
			if(opened == 0) {
				// save first opening position
				firstOpenedIndex = i;
			}
			opened++;
			continue;
		} else if(c == ')') {
			closed++;
			if(opened == closed) {
				string innerExpression = input.substr(firstOpenedIndex + 1, i - firstOpenedIndex - 1);
				number = calculate(innerExpression);
				if(errorFlag) {
					return CalculationParsingResult();
				}
			}
			continue;
		}

		// if we are in a bracket term we do not need to parse further here
		if(opened != closed) {
			continue;
		}

		//
		if(lastOp == i - 1 && c == '-') {
			numberSign *= -1;
			continue;
		}

		if(find(leftOps, c) || find(rightOps, c)) {
			// if we encounter an operator, save last number and operator and reset variables
			numbers.push_back(number * numberSign);
			operations.push_back(string(1, c));

			number = 0;
			decimalPosition = 1;
			numberSign = 1;
			greaterZero = true;
			lastOp = i;
		} else if(c == '.') {
			// after a period we have to add decimal digits
			greaterZero = false;
		} else if(c >= 'a' && c <= 'z') {
			// characters are only used for functions so far
			func += c;
		} else if(c >= '0' && c <= '9') {
			// add digit 
			if(greaterZero) {
				number *= 10;
				number += c - '0';
			} else {
				int digit = c - '0';
				double exponent = pow(10, -(decimalPosition++));
				number += (digit * exponent);
			}		
		} else {
			stringstream ss;
			ss << "unknown sign: " << c;
			error = ss.str();
			errorFlag = true;
			return CalculationParsingResult();
		}	
	}
	// add last token (number)
	numbers.push_back(number * numberSign);

#ifdef DEBUG
	cout << "numbers:" << endl;
	for(double n : numbers) {
		cout << n << " ";
	}
	cout << endl << "operations:" << endl;
	for(string o : operations) {
		cout << o << " ";
	}
	cout << endl;
#endif
	errorFlag = false;
	return result;
}

