#include "calc.h"


#define FUNC(n, x) [](double n) {x}

typedef double (*function)(double number);
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
vector<vector<char>> rightOps = {{}, {'^'}, {}, {}};
vector<vector<char>> leftOps = {{}, {}, {'*', '/'}, {'+', '-'}};

double doCalculation(double num1, double num2, char op) {
	switch(op) {
		case '*': return num1 * num2;
		case '/': return num1 / num2;
		case '+': return num1 + num2;
		case '-': return num1 - num2;
		case '^': return pow(num1, num2);
	}
	cerr << "unknown operator: " << op << endl;
	return 0;
}

double calc(string input)
{
	vector<double> numbers;
	vector<string> operations;
	
	double result = 0.0;

	bool greaterZero = true;
	int decimalPosition = 1;
	double number = 0;

	int opened = 0;
	int firstOpenedIndex = -1;
	int closed = 0;
	int lastOp = -1;
	int numberSign = 1;
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
		} else if(c == ')') {
			closed++;
			if(opened == closed) {
				string innerExpression = input.substr(firstOpenedIndex + 1, i - firstOpenedIndex - 1);
				number = calc(innerExpression);
			}
			continue;
		}

		if(opened != closed) {
			continue;
		}

		if(lastOp == i - 1 && c == '-') {
			numberSign *= -1;
			continue;
		}

		if(find(leftOps, c) || find(rightOps, c)) {
			numbers.push_back(number * numberSign);
			numberSign = 1;
			operations.push_back(string(1, c));
			number = 0;
			greaterZero = true;
			lastOp = i;
		} else if(c == '.') {
			greaterZero = false;
		} else if(c >= 'a' && c <= 'z') {
			func += c;
		} else if(c >= '0' && c <= '9') {
			if(greaterZero) {
				number *= 10;
				number += c - '0';
			} else {
				int digit = c - '0';
				double exponent = pow(10, -(decimalPosition++));
				number += (digit * exponent);
			}		
		} else {
			cerr << "unknown sign: " << c << endl;
			return -1;
		}	
	}
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

	// precedences:
	// 0: functions
	// 1: ^
	// 2: * /
	// 3: + -
	for(int precedence = 0; precedence < 4; precedence++) {
		if(precedence == 1) {
			for(int i = operations.size() - 1; i >= 0; i--) {
				if(operations[i].size() == 1 && find(rightOps[precedence], operations[i][0])) {
#ifdef DEBUG
					cout << "do: " << numbers[i] << operations[i] << numbers[i + 1];
#endif
					numbers[i] = doCalculation(numbers[i], numbers[i + 1], operations[i][0]);
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
					if(operations[i].size() > 1) {
						if(functions.find(operations[i]) != functions.end()) {
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
							cerr << "unknown function: " << operations[i] << endl;
							return -1;
						}
					}
				} else if(precedence >= 2) {
					if(operations[i].size() == 1 && find(leftOps[precedence], operations[i][0])) {
#ifdef DEBUG
						cout << "do: " << numbers[i] << operations[i] << numbers[i + 1];
#endif
						numbers[i] = doCalculation(numbers[i], numbers[i + 1], operations[i][0]);
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

	result = numbers[0];
	return result;
}
