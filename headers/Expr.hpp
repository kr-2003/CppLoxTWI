#pragma once

#ifndef EXPR_HPP
#define EXPR_HPP

#include <any>
#include <memory>
#include <vector>
#include <utility>
#include "Token.hpp"

class Assign;
class Binary;
class Grouping;
class Literal;
class Unary;
class Variable;

class ExprVisitor
{
public:
    virtual std::any visitAssignExpr(std::shared_ptr<Assign> expr) = 0;
    virtual std::any visitBinaryExpr(std::shared_ptr<Binary> expr) = 0;
    virtual std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) = 0;
    virtual std::any visitLiteralExpr(std::shared_ptr<Literal> expr) = 0;
    virtual std::any visitUnaryExpr(std::shared_ptr<Unary> expr) = 0;
    virtual std::any visitVariableExpr(std::shared_ptr<Variable> expr) = 0;
    virtual ~ExprVisitor() = default;
};

class Expr
{
public:
    virtual std::any accept(ExprVisitor& visitor) = 0;
};

class Assign : public Expr, public std::enable_shared_from_this<Assign>
{
public:
    Token name;
    std::shared_ptr<Expr> value;
public:
    Assign(Token name, std::shared_ptr<Expr> value) : name(name), value(value) {}
    std::any accept(ExprVisitor& visitor) override
    {
        return visitor.visitAssignExpr(shared_from_this());
    }
};

class Binary : public Expr, public std::enable_shared_from_this<Binary>
{
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
public:
    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) {}
    std::any accept(ExprVisitor& visitor) override
    {
        return visitor.visitBinaryExpr(shared_from_this());
    }
};

class Grouping : public Expr, public std::enable_shared_from_this<Grouping>
{
public:
    std::shared_ptr<Expr> expression;
public:
    Grouping(std::shared_ptr<Expr> expression) : expression(expression) {}
    std::any accept(ExprVisitor& visitor) override
    {
        return visitor.visitGroupingExpr(shared_from_this());
    }
};

class Literal : public Expr, public std::enable_shared_from_this<Literal>
{
public:
    std::any value;
public:
    Literal(std::any value) : value(value) {}
    std::any accept(ExprVisitor& visitor) override
    {
        return visitor.visitLiteralExpr(shared_from_this());
    }
};

class Unary : public Expr, public std::enable_shared_from_this<Unary>
{
public:
    Token op;
    std::shared_ptr<Expr> right;
public:
    Unary(Token op, std::shared_ptr<Expr> right) : op(op), right(right) {}
    std::any accept(ExprVisitor& visitor) override
    {
        return visitor.visitUnaryExpr(shared_from_this());
    }
};

class Variable : public Expr, public std::enable_shared_from_this<Variable>
{
public:
    Token name;
public:
    Variable(Token name) : name(name) {}
    std::any accept(ExprVisitor& visitor) override
    {
        return visitor.visitVariableExpr(shared_from_this());
    }
};


#endif