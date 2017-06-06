#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>

#include "Parser.h"


typedef std::function<Parser::Number(std::shared_ptr<Expression>, std::shared_ptr<Expression>)>
OperatorFunction;
typedef std::function<Parser::Number(const Parser::Number)> Function;

#define OP(value1, value2, body) [](std::shared_ptr<Expression> __param1, std::shared_ptr<Expression> __param2) -> Parser::Number \
    {\
        Parser::Number value1 = __param1->getValue(), value2 = __param2->getValue();\
        return body;\
    }

#define FN(v, body) [](const Parser::Number v) -> Parser::Number { return body; }

class Expression
{
        friend class Parser;
        
    private:
        struct Operator {
            size_t priority;
            OperatorFunction f;
        };
        
    public:
        Expression() {}
        Expression(std::shared_ptr<Expression>);
        virtual ~Expression() {}
        
        virtual Parser::Number getValue() const;
        
        
        static void AddOperator(char op, size_t priority, const OperatorFunction f)
        {
            operatorMap[op] = {priority, f};
        }
        
        static void AddFunction(const std::string &functionName, const Function &f)
        {
            functionMap[functionName] = f;
        }
        
    protected:
        std::list<std::shared_ptr<Expression>> expressions;
        std::list<Operator> operators;
        
        static std::map<char, Operator> operatorMap;
        static std::map<std::string, Function> functionMap;
        
};

class NumberExpression : public Expression
{
    public:
        NumberExpression(const Parser::Number value) : value(value) {}
        NumberExpression(const Expression &expr) : value(expr.getValue()) {}
        virtual ~NumberExpression() {}
        
        virtual Parser::Number getValue() const override
        {
            return value;
        }
        
    private:
        Parser::Number value;
};

typedef Expression BracketExpression;

class FunctionExpression : public Expression
{
    public:
        FunctionExpression(const std::string &f, std::shared_ptr<Expression> expr);
        virtual ~FunctionExpression() {}
        
        virtual Parser::Number getValue() const override;
        
    protected:
        std::string function;
        std::shared_ptr<Expression> arg;
};


//
// TODO: assignments are not implemented yet!
//
class AssignmentExpression : public Expression
{
    public:
        AssignmentExpression() {}
        virtual ~AssignmentExpression() {}
        
    private:
        std::string variable;
};

#endif // EXPRESSION_H