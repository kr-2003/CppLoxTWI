#pragma once

#ifndef STMT_HPP
#define STMT_HPP

#include <any>
#include <memory>
#include <vector>
#include <utility>
#include "Token.hpp"

class Block;
class Expression;
class Print;
class Var;
class If;
class While;

class StmtVisitor
{
public:
    virtual std::any visitBlockStmt(std::shared_ptr<Block> expr) = 0;
    virtual std::any visitExpressionStmt(std::shared_ptr<Expression> expr) = 0;
    virtual std::any visitPrintStmt(std::shared_ptr<Print> expr) = 0;
    virtual std::any visitVarStmt(std::shared_ptr<Var> expr) = 0;
    virtual std::any visitIfStmt(std::shared_ptr<If> expr) = 0;
    virtual std::any visitWhileStmt(std::shared_ptr<While> expr) = 0;
    virtual ~StmtVisitor() = default;
};

class Stmt
{
public:
    virtual std::any accept(StmtVisitor& visitor) = 0;
};

class Block : public Stmt, public std::enable_shared_from_this<Block>
{
public:
    std::vector<std::shared_ptr<Stmt>> statements;
public:
    Block(std::vector<std::shared_ptr<Stmt>> statements) : statements(std::move(statements)) {}
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitBlockStmt(shared_from_this());
    }
};

class Expression : public Stmt, public std::enable_shared_from_this<Expression>
{
public:
    std::shared_ptr<Expr> expression;
public:
    Expression(std::shared_ptr<Expr> expression) : expression(expression) {}
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitExpressionStmt(shared_from_this());
    }
};

class Print : public Stmt, public std::enable_shared_from_this<Print>
{
public:
    std::shared_ptr<Expr> expression;
public:
    Print(std::shared_ptr<Expr> expression) : expression(expression) {}
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitPrintStmt(shared_from_this());
    }
};


class Var : public Stmt, public std::enable_shared_from_this<Var>
{
public:
    Token name;
    std::shared_ptr<Expr> initializer;
public:
    Var(Token name, std::shared_ptr<Expr> initializer) : name(name), initializer(initializer) {}
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitVarStmt(shared_from_this());
    }
};

class If : public Stmt, public std::enable_shared_from_this<If>
{
public:
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> thenBranch;
    std::shared_ptr<Stmt> elseBranch;
public:
    If(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> thenBranch, std::shared_ptr<Stmt> elseBranch) : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitIfStmt(shared_from_this());
    }
};

class While : public Stmt, public std::enable_shared_from_this<While>
{
public:
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> body;
public:
    While(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> body) : condition {std::move(condition)}, body {std::move(body)} {}
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitWhileStmt(shared_from_this());
    }
};


#endif