#include "calculator.h"

using namespace std;

int main(int argc, const char* argv[])
{
	if(argc > 1) {
		cout << calculate(string(argv[1]));	
	} else {
		const vector<char> whitespaces = {' ', '\r', '\n', '\t'};
		std::string input;
		stringstream ss;

		cout << "> ";		
		getline(cin, input);
		do {
			ss.str("");
			for(char c : input) {
				if(!find(whitespaces, c)) {
					ss << c;
				}
			}
			cout << calculate(ss.str()) << endl;
			if(errorFlag) {
				break;
			}			

			cout << "> ";		
			getline(cin, input);
		} while(input != "");
	}

	if(errorFlag) {
		cerr << "Program exited with error: \"" << error << "\"" << endl;
	}

	return 0;
}
