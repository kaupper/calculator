#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <functional>

#include "Parser.h"


typedef std::function<Parser::Number(const Expression &, const Expression &)>
Operator;
typedef std::function<Parser::Number(const Parser::Number)> Function;

#define OP(param1, param2, body) [](const Expression &param1, const Expression &param2) -> Parser::Number { return body; }
#define FN(v, body) [](const Parser::Number v) -> Parser::Number { return body; }

class Expression
{
        friend class Parser;
        
    public:
        Expression() {}
        Expression(std::shared_ptr<Expression>);
        virtual ~Expression() {}
        
        virtual Parser::Number getValue() const;
        
        
        static void AddOperator(char op, const Operator f)
        {
            operatorMap[op] = f;
        }
        
        static void AddFunction(const std::string &functionName, const Function &f)
        {
            functionMap[functionName] = f;
        }
        
    protected:
        std::vector<std::shared_ptr<Expression>> expressions;
        std::vector<Operator> operators;
        
        static std::map<char, Operator> operatorMap;
        static std::map<std::string, Function> functionMap;
};

class NumberExpression : public Expression
{
    public:
        NumberExpression(const Parser::Number value) : value(value) {}
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



class AssignmentExpression : public Expression
{
    public:
        AssignmentExpression() {}
        virtual ~AssignmentExpression() {}
        
    private:
        std::string variable;
};

#endif // EXPRESSION_H