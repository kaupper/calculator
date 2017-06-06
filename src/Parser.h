#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <cmath>
#include <cctype>


class Expression;
class AssignmentExpression;
class Parser
{
    public:
        static AssignmentExpression ParseString(const std::string &calculation);
        static std::shared_ptr<Expression> ParseExpression(const std::string &expr);
        
        typedef long double Number;
        static std::function<Number(const std::string &)> toNumber;
};

#include "Expression.h"

#endif // PARSER_H