#ifndef RESOLVER_HPP
#define RESOLVER_HPP

#include <memory>
#include <map>

#include "Expr.hpp"
#include "Stmt.hpp"
#include "Interpreter.hpp"
#include "Token.hpp"


class Resolver : public ExprVisitor, public StmtVisitor
{
private:
    Interpreter& interpreter;
    std::vector<std::map<std::string, bool>> scopes;

    enum class FunctionType
    {
        NONE,
        FUNCTION,
        INITIALIZER,
        METHOD
    };

    enum class ClassType
    {
        NONE,
        CLASS,
        SUBCLASS
    };

    FunctionType currentFunction = FunctionType::NONE;
    ClassType currentClass = ClassType::NONE;

public:
    Resolver(Interpreter& interpreter) : interpreter {interpreter} {}

    std::any visitBlockStmt(std::shared_ptr<Block> stmt) override;
    std::any visitVarStmt(std::shared_ptr<Var> stmt) override;
    std::any visitFunctionStmt(std::shared_ptr<Function> function) override;
    std::any visitVariableExpr(std::shared_ptr<Variable> expr) override;
    std::any visitAssignExpr(std::shared_ptr<Assign> expr) override;
    std::any visitExpressionStmt(std::shared_ptr<Expression> stmt) override;
    std::any visitIfStmt(std::shared_ptr<If> stmt) override;
    std::any visitPrintStmt(std::shared_ptr<Print> stmt) override;
    std::any visitReturnStmt(std::shared_ptr<Return> stmt) override;
    std::any visitWhileStmt(std::shared_ptr<While> stmt) override;
    std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;
    std::any visitCallExpr(std::shared_ptr<Call> expr) override;
    std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
    std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
    std::any visitLogicalExpr(std::shared_ptr<Logical> expr) override;
    std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
    std::any visitClassStmt(std::shared_ptr<Class> stmt) override;
    std::any visitGetExpr(std::shared_ptr<Get> expr) override;
    std::any visitSetExpr(std::shared_ptr<Set> expr) override;
    std::any visitThisExpr(std::shared_ptr<This> expr) override;
    std::any visitSuperExpr(std::shared_ptr<Super> expr) override;
    void resolve(std::vector<std::shared_ptr<Stmt>> statements);

private:
    void resolve(std::shared_ptr<Stmt> stmt);
    void resolve(std::shared_ptr<Expr> expr);
    void beginScope();
    void endScope();
    void declare(Token& name);
    void define(Token& name);
    void resolveLocal(std::shared_ptr<Expr> expr, Token& name);
    void resolveFunction(std::shared_ptr<Function> stmt, FunctionType type);
};

#endif // RESOLVER_HPP