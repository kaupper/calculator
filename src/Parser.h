#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <sstream>
#include <functional>


class Expression;
class Parser
{
    public:
        static std::shared_ptr<Expression> Parse(const std::string &expr);
        
        typedef long double Number;
        static std::function<Number(const std::string &)> toNumber;
};

#include "Expression.h"

#endif // PARSER_H