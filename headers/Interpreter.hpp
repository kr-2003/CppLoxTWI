#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Expr.hpp"
#include "RuntimeError.hpp"
#include "Errors.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include <any>
#include <iostream>
#include <string>
#include <memory>

class Interpreter : public ExprVisitor
{
public:
    void interpret(std::shared_ptr<Expr> expression);

    std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;

private:
    std::any evaluate(std::shared_ptr<Expr> expr);
    bool isTruthy(std::any object);
    bool isEqual(const std::any &a, const std::any &b);

    void checkNumberOperand(Token op, std::any operand);
    void checkNumberOperands(Token op, std::any left, std::any right);

    std::string stringify(std::any object);
};

#endif // INTERPRETER_HPP
