#ifndef NUMBEREXPRESSION_H
#define NUMBEREXPRESSION_H

#include "expression.h"

class NumberExpression : public Expression
{
    private:
        static std::map<std::string, double (*)(double)> functions;
        
        static const std::vector<std::vector<char>> leftOps;
        static const std::vector<std::vector<char>> rightOps;
        
        static std::string doCalculation(NumberExpression &, NumberExpression &, char);
        static std::string doCalculation(NumberExpression &, std::string);
        
        std::vector<NumberExpression> numbers;
        std::vector<std::string> operations;
        
        void _process() override;
        void _parse() override;
        double _resolveValue() override;
        
    public:
        NumberExpression() : NumberExpression("") {}
        NumberExpression(const std::string &exp) : Expression(exp) { }
};

#endif