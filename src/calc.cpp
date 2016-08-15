#include "calc.h"


#define FUNC(n, x) [](double n) {x}

typedef double (*function)(double number);
static map<string, function> functions = {
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
static const vector<vector<char>> rightOps = {{}, {'^'}, {}, {}};
static const vector<vector<char>> leftOps = {{}, {}, {'*', '/'}, {'+', '-'}};

static double doCalculation(double num1, double num2, char op) {
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

ParsingResult parse(string input) 
{
	ParsingResult result;
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
				number = calc(innerExpression);
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
			cerr << "unknown sign: " << c << endl;
			return ParsingResult();
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

	return result;
}

double process(ParsingResult parsedInput)
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
							cerr << "unknown function: " << operations[i] << endl;
							return -1;
						}
					}
				} else if(precedence >= 2) {
					// process * and /, + and - calls
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

	return numbers[0];
}

double calc(string input)
{
	ParsingResult parsedInput = parse(input);
	double result = process(parsedInput);
	return result;
}
