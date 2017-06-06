#ifndef FORMALEXPRESSION_H
#define FORMALEXPRESSION_H

#include "calculator.h"

class FormalExpression : public Expression
{
    private:
        static const std::vector<std::string> expressionOps;
        /*
        LeftHandSide lhs;
        RightHandSide rhs;
        */
        std::string operation;
        
        void _process() override;
        void _parse() override;
        double _resolveValue() override;
        
    public:
        FormalExpression() : FormalExpression("") { }
        FormalExpression(const std::string &exp) : Expression(exp) { }
};

#endif