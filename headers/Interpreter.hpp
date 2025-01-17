#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Expr.hpp"
#include "RuntimeError.hpp"
#include "Errors.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "Stmt.hpp"
#include "Environment.hpp"
#include <any>
#include <iostream>
#include <string>
#include <memory>

class Interpreter : public ExprVisitor, public StmtVisitor
{
public:
    void interpret(std::vector<std::shared_ptr<Stmt>> statements);
    void executeBlock(std::vector<std::shared_ptr<Stmt>> statements, std::shared_ptr<Environment> environment);

    std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    std::any visitVariableExpr(std::shared_ptr<Variable> expr) override;
    std::any visitAssignExpr(std::shared_ptr<Assign> expr) override;

    std::any visitBlockStmt(std::shared_ptr<Block> expr) override;
    std::any visitExpressionStmt(std::shared_ptr<Expression> expr) override;
    std::any visitPrintStmt(std::shared_ptr<Print> expr) override;
    std::any visitVarStmt(std::shared_ptr<Var> expr) override;

private:
    std::shared_ptr<Environment> environment = std::make_shared<Environment>();
    std::any evaluate(std::shared_ptr<Expr> expr);
    bool isTruthy(std::any object);
    bool isEqual(const std::any &a, const std::any &b);

    void checkNumberOperand(Token op, std::any operand);
    void checkNumberOperands(Token op, std::any left, std::any right);

    std::string stringify(std::any object);
    void execute(std::shared_ptr<Stmt> stmt);

};

#endif // INTERPRETER_HPP
