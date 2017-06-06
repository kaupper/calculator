# calculator
A simple calculator written in C++

Currently (2017/06/06) supported are bracket terms, custom functions and custom operators (no operator precedence!).

# Usage example

```c++
    #include <memory>
    #include <iostream>
    #include <string>
    
    #include "Parser.h"
    
    int main() 
    {
        // Parser::Number is the data type which is used for calculations internally
        // (long double atm)
        
        //
        // add custom operators
        //
        // first argument takes the character representation of the operator (only single char operators are supported)
        // the second argument takes a function with the signature
        //     Parser::Number(const Expression &, const Expression &)
        // OP is a macro for this, the first two parameters being the names of the parameters and the third one
        // being an expression which should directly return the value
        // (see Expression.h for implementation)
        Expression::AddOperator('+', OP(e1, e2, e1.getValue() + e2.getValue()));
        Expression::AddOperator('*', OP(e1, e2, e1.getValue() * e2.getValue()));
        
        //
        // add custom function
        //
        // first argument takes the string representation of the operator (only alpha numerical names are supported)
        // the second argument takes a function with the signature
        //     Parser::Number(const Parser::Number)
        // FN is a macro for this, the first parameter being the names of the parameter and the second one
        // being an expression which should directly return the value
        // (see Expression.h for implementation)
        Expression::AddFunction("twice", FN(v, v * 2));

        try {
            // ParseException max throw if the format is not valid
            std::shared_ptr<Expression> expr = Parser::ParseExpression("(twice(1)+2)*(2+3)");
            
            // expected output is '(twice(1)+2)*(2+3)=20'
            std::cout << "(twice(1)+2)*(2+3)=" << expr->getValue() << std::endl;
        } catch (const std::string &ex) {
            std::cerr << ex << std::endl;
            return 1;
        }
        
        return 0;
    }
```
