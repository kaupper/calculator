#include "calculator.h"

using namespace std;

int main(int argc, const char* argv[])
{
	bool silent = false;
	string calculation = "";
	std::string error;
	
	for(int i = 1; i < argc; i++) {
		string arg = string(argv[i]);
		if(arg == "-q" || arg == "--quiet" || arg == "-s" || arg == "--silent") {
			silent = true;
		} else {
			calculation = arg;
		}
	}
	 
	if(calculation != "") {
		cout << calculate(calculation) << endl;
		if((error = NumberExpression::getError()) != "") {
			cerr << error << endl;
			return -1;
		}
		return 0;
	}

	const vector<char> whitespaces = {' ', '\r', '\n', '\t'};
	std::string input;
	std::stringstream ss;
	
	if(!silent) {
		cout << "> ";	
	}
	getline(cin, input);
	do {
		ss.str("");
		for(char c : input) {
			if(!find(whitespaces, c)) {
				ss << c;
			}
		}
		cout << calculate(ss.str()) << endl;
		
		if((error = NumberExpression::getError()) != "") {
			cerr << error << endl;
		}
		
		if(!silent) {
			cout << "> ";
		}
		getline(cin, input);
	} while(input != "");
	
	return 0;
}
