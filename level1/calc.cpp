#include "calc.h"

vector<int> numbers;
vector<char> operators;

static char ops[] = {'+', '-'};

double calc(string input)
{
	int result = 0;
	int number = 0;

	// extract numbers and operators
	for(char c : input) {
		if(c == ops[0] || c == ops[1]) {
			numbers.push_back(number);
			operators.push_back(c);
			number = 0;
		} else {
			number *= 10;
			number += (int)(c - '0');
		}
	}
	numbers.push_back(number);
	
	result = numbers[0];
	for(int i = 0; i < operators.size(); i++) {
		char c = operators[i];
		switch(c) {
			case '+':
				result += numbers[i + 1];
				break;
			case '-':
				result -= numbers[i + 1];
		}
	}


	return result;
}
