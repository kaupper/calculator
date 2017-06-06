#include "Expression.h"


std::map<std::string, Function> Expression::functionMap;
std::map<char, Expression::Operator> Expression::operatorMap;


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
    } else if (operators.size() == 0) {
        return expressions.front()->getValue();
    }
    
    auto predicate = [](auto & e1, auto & e2) {
        return e1.priority < e2.priority;
    };
    size_t maxPriority = std::max_element(operators.cbegin(),
                                          operators.cend(),
                                          predicate)->priority;
    // make a copy of the list because we need to modify them
    auto operators = this->operators;
    auto expressions = this->expressions;
    
    for (size_t p = maxPriority; ; --p) {
        auto currentOperator = operators.begin();
        auto currentExpression = expressions.begin();
        
        while (currentOperator != operators.end()) {
            if (currentOperator->priority == p) {
                // execute the operator on the current and the next expression
                auto tmpEx = currentOperator->f(*currentExpression,
                                                *std::next(currentExpression));
                // override current expressions value
                *currentExpression = std::make_shared<NumberExpression>(tmpEx);
                // erase operator and next expression
                currentOperator = operators.erase(currentOperator);
                expressions.erase(std::next(currentExpression));
            } else {
                ++currentExpression;
                ++currentOperator;
            }
        }
        
        if (p == 0) {
            break;
        }
    }
    
    return expressions.front()->getValue();
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