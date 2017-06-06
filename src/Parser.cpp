#include "Parser.h"


std::function<Parser::Number(const std::string &)> Parser::toNumber =
[](const std::string &s) -> Parser::Number {
    return std::stold(s);
};


static std::shared_ptr<Expression> getBracketExpression(const std::string &expr,
        size_t &bracketIndex)
{
    size_t openings = 0;
    size_t closingBracket;
    
    for (size_t i = bracketIndex; i < expr.size(); ++i) {
        if (expr[i] == ')') {
            --openings;
            
            if (openings == 0) {
                closingBracket = i;
                break;
            }
        } else if (expr[i] == '(') {
            ++openings;
        }
    }
    
    if (closingBracket == std::string::npos) {
        throw std::string("Invalid number of brackets!");
    } else {
        auto tmp = Parser::Parse(expr.substr(bracketIndex + 1,
                                             closingBracket - bracketIndex - 1));
        bracketIndex = closingBracket;
        return tmp;
    }
}

std::shared_ptr<Expression> Parser::Parse(std::string expr)
{
    auto newEnd = std::remove_if(expr.begin(), expr.end(),
    [](auto c) {
        return std::isspace(c);
    });
    expr.resize(std::distance(expr.begin(), newEnd));
    return ParseExpression(expr);
}

std::shared_ptr<Expression> Parser::ParseExpression(const std::string &expr)
{
    std::shared_ptr<Expression> expression = std::make_shared<Expression>();
    std::stringstream number;
    std::stringstream function;
    
    for (size_t i = 0; i < expr.size(); ++i) {
        const char c = expr[i];
        
        // parse a function name
        if (function.tellp() != 0) {
            if (c == '(') {
                expression->expressions.push_back(std::make_shared<FunctionExpression>
                                                  (function.str(), getBracketExpression(expr, i)));
                function.str("");
                continue;
            } else if (std::isalnum(c)) {
                function << c;
                continue;
            } else {
                throw std::string("A function name has to contain of alpha numerical characters!");
            }
        }
        
        // parse a number
        if (number.tellp() != 0) {
            if (std::isdigit(c) || c == '.') {
                number << c;
                continue;
            } else {
                expression->expressions.push_back(std::make_shared<NumberExpression>
                                                  (toNumber(number.str())));
                number.str("");
            }
        }
        
        if (c == '(') {
            // parse  a bracket expression
            expression->expressions.push_back(getBracketExpression(expr, i));
        } else if (std::isdigit(c) || c == '.') {
            // start parsing a number
            number << c;
        } else if (Expression::operatorMap.find(c) != Expression::operatorMap.end()) {
            // found an operator
            expression->operators.push_back(Expression::operatorMap[c]);
        } else if (std::isalpha(c)) {
            // start parsing a function
            function << c;
        } else {
            throw std::string("Invalid character '" + std::string(1, c) + "'");
        }
    }
    
    // parse a function name
    if (function.tellp() != 0) {
        throw std::string("A function '" + function.str() + "' got no argument");
    }
    
    // parse a number
    if (number.tellp() != 0) {
        expression->expressions.push_back(std::make_shared<NumberExpression>
                                          (toNumber(number.str())));
        number.str("");
    }
    
    return expression;
}
