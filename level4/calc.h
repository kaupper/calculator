#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

double calc(std::string calculation);

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

#endif
