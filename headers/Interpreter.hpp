#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Expr.hpp"
#include "RuntimeError.hpp"
#include "Errors.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "Stmt.hpp"
#include "Environment.hpp"
#include "LoxCallable.hpp"
#include "LoxFunction.hpp"
#include "LoxReturn.hpp"
#include "LoxClass.hpp"
#include <any>
#include <iostream>
#include <string>
#include <memory>
#include <map>

class NativeClock : public LoxCallable
{
public:
    int arity()override;
    std::any call(Interpreter& interpreter, std::vector<std::any> arguments) override;
    std::string toString() override;

};

class Interpreter : public ExprVisitor, public StmtVisitor
{
public:
    Interpreter();
    void interpret(std::vector<std::shared_ptr<Stmt>> statements);
    void executeBlock(std::vector<std::shared_ptr<Stmt>> statements, std::shared_ptr<Environment> environment);
    void resolve(std::shared_ptr<Expr> expr, int depth);

    std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    std::any visitVariableExpr(std::shared_ptr<Variable> expr) override;
    std::any visitAssignExpr(std::shared_ptr<Assign> expr) override;
    std::any visitLogicalExpr(std::shared_ptr<Logical> expr) override;
    std::any visitCallExpr(std::shared_ptr<Call> expr) override;
    std::any visitGetExpr(std::shared_ptr<Get> expr) override;
    std::any visitSetExpr(std::shared_ptr<Set> expr) override;

    std::any visitBlockStmt(std::shared_ptr<Block> expr) override;
    std::any visitExpressionStmt(std::shared_ptr<Expression> expr) override;
    std::any visitPrintStmt(std::shared_ptr<Print> expr) override;
    std::any visitVarStmt(std::shared_ptr<Var> expr) override;
    std::any visitIfStmt(std::shared_ptr<If> expr) override;
    std::any visitWhileStmt(std::shared_ptr<While> expr) override;
    std::any visitFunctionStmt(std::shared_ptr<Function> expr) override;
    std::any visitReturnStmt(std::shared_ptr<Return> expr) override;
    std::any visitClassStmt(std::shared_ptr<Class> stmt) override;

public:
    std::shared_ptr<Environment> globals{new Environment};
    

private:
    std::shared_ptr<Environment> environment = globals;
    std::map<std::shared_ptr<Expr>, int> locals;
    std::any evaluate(std::shared_ptr<Expr> expr);
    bool isTruthy(std::any object);
    bool isEqual(const std::any &a, const std::any &b);

    void checkNumberOperand(Token op, std::any operand);
    void checkNumberOperands(Token op, std::any left, std::any right);

    std::string stringify(std::any object);
    void execute(std::shared_ptr<Stmt> stmt);
    std::any lookUpVariable(Token& name, std::shared_ptr<Expr> expr);

};

#endif // INTERPRETER_HPP
