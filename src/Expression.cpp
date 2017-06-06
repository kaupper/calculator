#include "Expression.h"


std::map<std::string, Function> Expression::functionMap;
std::map<char, Operator> Expression::operatorMap;


Expression::Expression(std::shared_ptr<Expression> expr)
{
    std::copy(expr->expressions.cbegin(), expr->expressions.cend(),
              std::back_inserter(expressions));
    std::copy(expr->operators.cbegin(), expr->operators.cend(),
              std::back_inserter(operators));
}

Parser::Number Expression::getValue() const
{
    if (expressions.size() == 0) {
        return 0.0;
    }
    
    Parser::Number result = expressions[0]->getValue();
    
    for (size_t i = 1; i < expressions.size(); ++i) {
        result = operators[i - 1](NumberExpression(result), *expressions[i]);
    }
    
    return result;
}


FunctionExpression::FunctionExpression(const std::string &f,
                                       std::shared_ptr<Expression> expr) :
    function(f),
    arg(expr) {}

Parser::Number FunctionExpression::getValue() const
{
    if (functionMap.find(function) == functionMap.end()) {
        throw std::string("No function found for '" + function + "'.");
    }
    
    return functionMap[function](arg->getValue());
}