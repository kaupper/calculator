#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;

struct ParsingResult {
    vector<double> numbers;
    vector<string> operations;
};


double calc(std::string calculation);
ParsingResult parse(std::string input);
double process(ParsingResult);



const long double PI = 3.141592653589793238L;

template <class T> bool find(vector<T> v, T i)
{
	return find(v.begin(), v.end(), i) != v.end();
}

template <class T> bool find(vector<vector<T>> v, T i)
{
	for(auto iv : v) {
		if(find(iv, i)) {
			return true;
		}
	}
	return false;
}

template <class T, class U> bool find(map<T, U> m, T k)
{
	return m.find(k) != m.end();
}

#endif
