#include "calc.h"

vector<double> numbers;
vector<char> operators;

vector<vector<char>> ops = {{'*', '/'}, {'+', '-'}};

double doCalculation(double num1, double num2, char op) {
	switch(op) {
		case '*': return num1 * num2;
		case '/': return num1 / num2;
		case '+': return num1 + num2;
		case '-': return num1 - num2;
	}
	cerr << "unknown operators" << endl;
	return 0;
}

double calc(string input)
{
	double result = 0.0;

	bool greaterZero = true;
	int decimalPosition = 1;
	double number = 0;
	for(char c : input) {
		if(find(ops, c)) {
			numbers.push_back(number);
			operators.push_back(c);
			number = 0;
			greaterZero = true;
		} else if(c == '.') {
			greaterZero = false;
		} else {
			if(greaterZero) {
				number *= 10;
				number += c - '0';
			} else {
				int digit = c - '0';
				double exponent = pow(10, -(decimalPosition++));
				number += (digit * exponent);
			}		
		}
	}
	numbers.push_back(number);

#ifdef DEBUG
	cout << "numbers:" << endl;
	for(double n : numbers) {
		cout << n << " ";
	}
	cout << endl << "operators:" << endl;
	for(char o : operators) {
		cout << o << " ";
	}
	cout << endl;
#endif

	for(int precedence = 0; precedence < 2; precedence++) {
		for(int i = 0; i < operators.size(); i++) {
			if(find(ops[precedence], operators[i])) {
#ifdef DEBUG
				cout << "do: " << numbers[i] << operators[i] << numbers[i + 1];
#endif
				numbers[i] = doCalculation(numbers[i], numbers[i + 1], operators[i]);
#ifdef DEBUG
				cout << "=" << numbers[i] << endl;
#endif

				numbers.erase(numbers.begin() + i + 1);
				operators.erase(operators.begin() + i);
				i--;
			}
		}
	}
#ifdef DEBUG
	cout << endl;
#endif
	result = numbers[0];
	return result;
}
