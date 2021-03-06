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
        static std::shared_ptr<Expression> Parse(std::string expr);
        
        typedef long double Number;
        static std::function<Number(const std::string &)> toNumber;
        
    private:
        static std::shared_ptr<Expression> ParseExpression(const std::string &expr);
};

#include "Expression.h"

#endif // PARSER_H