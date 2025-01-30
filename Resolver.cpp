#include "./headers/Resolver.hpp"

std::any Resolver::visitBlockStmt(std::shared_ptr<Block> stmt)
{
    // std::cout << "In visitBlockStmt" << std::endl;
    beginScope();
    // std::cout << "Beginscope done" << std::endl;
    resolve(stmt->statements);
    // std::cout << "resolve in visitBlockstmt done" << std::endl;
    endScope();
    // std::cout << "Out visitBlockStmt" << std::endl;
    return nullptr;
}

std::any Resolver::visitVarStmt(std::shared_ptr<Var> stmt)
{
    declare(stmt->name);
    if(stmt->initializer != nullptr)
    {
        resolve(stmt->initializer);
    }
    define(stmt->name);
    return nullptr;
}

std::any Resolver::visitFunctionStmt(std::shared_ptr<Function> stmt)
{
    declare(stmt->name);
    define(stmt->name);

    resolveFunction(stmt, FunctionType::FUNCTION);
    return nullptr;
}

std::any Resolver::visitVariableExpr(std::shared_ptr<Variable> expr)
{
    if(!scopes.empty())
    {
        auto& scope = scopes.back();
        auto elem = scope.find(expr->name.lexeme);
        if(elem != scope.end() && elem->second == false)
        {
            error(expr->name, "Can't read local variable in its own initializer.");
        }
    }

    resolveLocal(expr, expr->name);
    return {};
}

std::any Resolver::visitAssignExpr(std::shared_ptr<Assign> expr)
{
    resolve(expr->value);
    resolveLocal(expr, expr->name);
    return nullptr;
}

std::any Resolver::visitExpressionStmt(std::shared_ptr<Expression> stmt)
{
    resolve(stmt->expression);
    return nullptr;
}

std::any Resolver::visitIfStmt(std::shared_ptr<If> stmt)
{
    resolve(stmt->condition);
    resolve(stmt->thenBranch);
    if(stmt->elseBranch != nullptr) 
    {
        resolve(stmt->elseBranch);
    }
    return nullptr;
}

std::any Resolver::visitPrintStmt(std::shared_ptr<Print> stmt)
{
    resolve(stmt->expression);
    return {};
}

std::any Resolver::visitReturnStmt(std::shared_ptr<Return> stmt)
{
    if(currentFunction == FunctionType::NONE)
    {
        error(stmt->keyword, "Can't return from top-level code.");
    }

    if(stmt->value != nullptr)
    {
        resolve(stmt->value);
    }

    return nullptr;
}

std::any Resolver::visitWhileStmt(std::shared_ptr<While> stmt)
{
    resolve(stmt->condition);
    resolve(stmt->body);
    return nullptr;
}

std::any Resolver::visitBinaryExpr(std::shared_ptr<Binary> expr)
{
    resolve(expr->left);
    resolve(expr->right);
    return nullptr;
}

std::any Resolver::visitCallExpr(std::shared_ptr<Call> expr)
{
    resolve(expr->callee);

    for(std::shared_ptr<Expr> argument : expr->arguments)
    {
        resolve(argument);
    }

    return nullptr;
}

std::any Resolver::visitGroupingExpr(std::shared_ptr<Grouping> expr)
{
    resolve(expr->expression);
    return nullptr;
}

std::any Resolver::visitLiteralExpr(std::shared_ptr<Literal> expr)
{
    return nullptr;
}

std::any Resolver::visitLogicalExpr(std::shared_ptr<Logical> expr)
{
    resolve(expr->left);
    resolve(expr->right);
    return nullptr;
}

std::any Resolver::visitUnaryExpr(std::shared_ptr<Unary> expr)
{
    resolve(expr->right);
    return nullptr;
}

std::any Resolver::visitClassStmt(std::shared_ptr<Class> stmt)
{
    declare(stmt->name);
    define(stmt->name);

    for(std::shared_ptr<Function> method : stmt->methods)
    {
        FunctionType declaration = FunctionType::METHOD;
        resolveFunction(method, declaration);
    }
    
    return nullptr;
}

std::any Resolver::visitGetExpr(std::shared_ptr<Get> expr)
{
    resolve(expr->object);
    return nullptr;
}

std::any Resolver::visitSetExpr(std::shared_ptr<Set> expr)
{
    resolve(expr->value);
    resolve(expr->object);
    return nullptr;
}

void Resolver::resolve(std::vector<std::shared_ptr<Stmt>> statements)
{
    for(std::shared_ptr<Stmt> statement : statements) 
    {
        // std::cout << "Resolvinggggg in Resolver::resolve" << std::endl;
        resolve(statement);
    }
}

void Resolver::resolve(std::shared_ptr<Stmt> stmt) 
{
    // std::cout << "in resolve(std::shared_ptr<Stmt> stmt)" << std::endl;
    stmt->accept(*this);
}

void Resolver::resolve(std::shared_ptr<Expr> expr)
{
    expr->accept(*this);
}

void Resolver::beginScope()
{
    scopes.push_back(std::map<std::string, bool> {});
}

void Resolver::endScope()
{
    scopes.pop_back();
}

void Resolver::declare(Token& name)
{
    if(scopes.empty())
    {
        return;
    }

    std::map<std::string, bool> scope = scopes.back();

    if(scope.find(name.lexeme) != scope.end())
    {
        error(name, "Already a variable with this name in this scope.");
    }

    scope[name.lexeme] = false;
}

void Resolver::define(Token& name)
{
    if(scopes.empty())
    {
        return;
    }
    scopes.back()[name.lexeme] = true;
}

void Resolver::resolveLocal(std::shared_ptr<Expr> expr, Token& name)
{
    for(int i = scopes.size() - 1; i >= 0; i--) 
    {
        if(scopes[i].find(name.lexeme) != scopes[i].end())
        {
            interpreter.resolve(expr, scopes.size() - 1 - i);
            return;
        }
    }
}

void Resolver::resolveFunction(std::shared_ptr<Function> function, FunctionType type)
{
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;

    beginScope();
    for(Token& param : function->params)
    {
        declare(param);
        define(param);
    }
    resolve(function->body);
    endScope();

    currentFunction = enclosingFunction;
}