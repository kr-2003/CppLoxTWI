#pragma once

#ifndef STMT_HPP
#define STMT_HPP

#include <any>
#include <memory>
#include <vector>
#include <utility>
#include <iostream>
#include "Token.hpp"

class Block;
class Expression;
class Print;
class Var;
class If;
class While;
class Function;
class Return;
class Class;

class StmtVisitor
{
public:
    virtual std::any visitBlockStmt(std::shared_ptr<Block> expr) = 0;
    virtual std::any visitExpressionStmt(std::shared_ptr<Expression> expr) = 0;
    virtual std::any visitPrintStmt(std::shared_ptr<Print> expr) = 0;
    virtual std::any visitVarStmt(std::shared_ptr<Var> expr) = 0;
    virtual std::any visitIfStmt(std::shared_ptr<If> expr) = 0;
    virtual std::any visitWhileStmt(std::shared_ptr<While> expr) = 0;
    virtual std::any visitFunctionStmt(std::shared_ptr<Function> expr) = 0;
    virtual std::any visitReturnStmt(std::shared_ptr<Return> expr) = 0;
    virtual std::any visitClassStmt(std::shared_ptr<Class> expr) = 0;
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
        // std::cout << "In accept of block" << std::endl;
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

class Function : public Stmt, public std::enable_shared_from_this<Function> 
{
public:
    Token name;
    std::vector<Token> params;
    std::vector<std::shared_ptr<Stmt>> body;

public:
    Function(Token name, std::vector<Token> params, std::vector<std::shared_ptr<Stmt>> body) : name {std::move(name)}, params {std::move(params)}, body {std::move(body)} {};
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitFunctionStmt(shared_from_this());
    }
};

class Return : public Stmt, public std::enable_shared_from_this<Return> 
{
public:
    Token keyword;
    std::shared_ptr<Expr> value;

public:
    Return(Token keyword, std::shared_ptr<Expr> value) : keyword {std::move(keyword)}, value {std::move(value)} {};
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitReturnStmt(shared_from_this());
    }
};

class Class : public Stmt, public std::enable_shared_from_this<Class>
{
public:
    Token name;
    std::shared_ptr<Variable> superclass;
    std::vector<std::shared_ptr<Function>> methods;

public:
    Class(Token name, std::shared_ptr<Variable> superclass, std::vector<std::shared_ptr<Function>> methods) : name {std::move(name)}, superclass {std::move(superclass)}, methods {std::move(methods)} {}
    std::any accept(StmtVisitor& visitor) override
    {
        return visitor.visitClassStmt(shared_from_this());
    }
};


#endif