#include "expression.h"

void Expression::parse() {	
	if(parsed) {
		return;
	}
	
	if(hasError()) {
		return;
	}
	
	if(expression == "") {
		errorFlag = true;
		error = "expression must be set to parse";
		return;
	}
	
	_parse();
	
	if(!hasError()) {
		parsed = true;
	}
}

void Expression::process() {
	if(processed) {
		return;
	}
	
	if(hasError()) {
		return;
	}
	
	if(!parsed) {
		parse();
		if(!parsed) {
			return;
		}
	}
		
	if(value != null) {
		return;
	}
	
	_process();
	
	if(!hasError()) {
		processed = true;
	}
}

double Expression::resolveValue() {
	if(hasError()) {
		return;
	}
	
	if(resolved) {
		return doubleValue;
	}
	
	if(!parsed) {
		parse();
		if(!parsed) {
			return 0.0;
		}
	}
	
	if(!processed) {
		process();
		if(!processed) {
			return 0.0;
		}
	}
	
	_resolveValue();
	
	if(!hasError()) {
		resolved = true;
		return doubleValue;
	}
	
	return 0.0;
}