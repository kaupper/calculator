#include <iostream>
#include <iomanip>
#include <cmath>

#include "Parser.h"


static bool almost(Parser::Number d1, Parser::Number d2)
{
    static const Parser::Number epsilon = 0.001;
    return std::fabs((d2 - d1)) < epsilon;
}

int main()
{
    Expression::AddOperator('+', 1, OP(v1, v2, v1 + v2));
    Expression::AddOperator('-', 1, OP(v1, v2, v1 - v2));
    Expression::AddOperator('*', 2, OP(v1, v2, v1 * v2));
    Expression::AddOperator('/', 2, OP(v1, v2, v1 / v2));
    Expression::AddOperator('^', 3, OP(v1, v2, std::pow(v1, v2)));
    Expression::AddFunction("sin", FN(v, std::sin(v)));
    Expression::AddFunction("cos", FN(v, std::cos(v)));
    Expression::AddFunction("tan", FN(v, std::tan(v)));
    Expression::AddFunction("sqrt", FN(v, std::sqrt(v)));
    //
    std::string calculation = "";
    std::map<std::string, Parser::Number> tests = {
        {"9/(2+1)", 3.},
        {"9/ cos(2-2)", 9.},
        {"sin(0)", 0},
        {"cos(0)", 1},
        {"(sin(1234)^2)+(cos(1234)^2)", 1},
        {"2/3", 0.6666},
        {"sqrt(4)", 2.},
        {"sqrt(2)", 1.414},
        {"(1+2)*3", 9.},
        {"1+2*3", 7.},
        {"1.3-0.3", 1.},
        {"0.1 + 0.2", 0.3}
    } ;
    
    for (auto &test : tests) {
        try {
            auto expression = Parser::Parse(test.first);
            auto result = expression->getValue();
            std::cout << std::setw(45) << std::right << test.first << std::left
                      << std::string(5, ' ')
                      << result << (almost(result, test.second) ? "==" : "!=") << test.second
                      << std::endl;
        } catch (const std::string &ex) {
            std::cerr << test.first << std::endl;
            std::cerr << ex << std::endl;
            return 1;
        }
    }
    
    return 0;
}