#include "./headers/Interpreter.hpp"

void Interpreter::interpret(std::vector<std::shared_ptr<Stmt>> statements)
{
    try
    {
        for(std::shared_ptr<Stmt> statement : statements)
        {
            execute(statement);
        }
    }
    catch (RuntimeError &error)
    {
        runtimeError(error);
    }
}

std::any Interpreter::visitLiteralExpr(std::shared_ptr<Literal> expr)
{
    return expr->value;
}

std::any Interpreter::visitGroupingExpr(std::shared_ptr<Grouping> expr)
{
    return evaluate(expr->expression);
}

std::any Interpreter::visitUnaryExpr(std::shared_ptr<Unary> expr)
{
    std::any right = evaluate(expr->right);

    switch (expr->op.type)
    {
    case TokenType::MINUS:
        checkNumberOperand(expr->op, right);
        return -std::any_cast<double>(right);
    case TokenType::BANG:
        return !std::any_cast<bool>(right);
    default:
        return nullptr;
    }
}

std::any Interpreter::visitAssignExpr(std::shared_ptr<Assign> expr)
{
    std::any value = evaluate(expr->value);
    environment->assign(expr->name, value);
    return value;
}

std::any Interpreter::visitBinaryExpr(std::shared_ptr<Binary> expr)
{
    std::any left = evaluate(expr->left);
    std::any right = evaluate(expr->right);

    switch (expr->op.type)
    {
    case TokenType::MINUS:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) - std::any_cast<double>(right);
    case TokenType::SLASH:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) / std::any_cast<double>(right);
    case TokenType::STAR:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) * std::any_cast<double>(right);
    case TokenType::PLUS:
        if (left.type() == typeid(double) && right.type() == typeid(double))
        {
            return std::any_cast<double>(left) + std::any_cast<double>(right);
        }
        if (left.type() == typeid(std::string) && right.type() == typeid(std::string))
        {
            return std::any_cast<std::string>(left) + std::any_cast<std::string>(right);
        }
        throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
    case TokenType::GREATER:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) > std::any_cast<double>(right);
    case TokenType::GREATER_EQUAL:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) >= std::any_cast<double>(right);
    case TokenType::LESS:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) < std::any_cast<double>(right);
    case TokenType::LESS_EQUAL:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) <= std::any_cast<double>(right);
    case TokenType::BANG_EQUAL:
        return !isEqual(left, right);
    case TokenType::EQUAL_EQUAL:
        return isEqual(left, right);
    default:
        return nullptr;
    }
}

std::any Interpreter::visitVariableExpr(std::shared_ptr<Variable> expr)
{
    return environment->get(expr->name);
}

std::any Interpreter::visitExpressionStmt(std::shared_ptr<Expression> stmt)
{
    evaluate(stmt->expression);
    return nullptr;
}

std::any Interpreter::visitPrintStmt(std::shared_ptr<Print> stmt)
{
    std::any value = evaluate(stmt->expression);
    std::cout << stringify(value) << "\n";
    return nullptr;
}

std::any Interpreter::visitVarStmt(std::shared_ptr<Var> stmt)
{
    std::any value = nullptr;
    if (stmt->initializer != nullptr)
    {
        value = evaluate(stmt->initializer);
    }
    environment->define(stmt->name.lexeme, value);
    return nullptr;
}

std::any Interpreter::visitBlockStmt(std::shared_ptr<Block> stmt)
{
    executeBlock(stmt->statements, std::make_shared<Environment>(environment));
    return nullptr;
}

std::any Interpreter::evaluate(std::shared_ptr<Expr> expr)
{
    return expr->accept(*this);
}

bool Interpreter::isTruthy(std::any object)
{
    if (object.type() == typeid(bool))
    {
        return std::any_cast<bool>(object);
    }
    return object.has_value();
}

bool Interpreter::isEqual(const std::any &a, const std::any &b)
{
    if (a.type() == typeid(nullptr) && b.type() == typeid(nullptr))
    {
        return true;
    }

    if (a.type() == typeid(nullptr))
    {
        return false;
    }

    if (a.type() == typeid(double) && b.type() == typeid(double))
    {
        return std::any_cast<double>(a) == std::any_cast<double>(b);
    }

    if (a.type() == typeid(std::string) && b.type() == typeid(std::string))
    {
        return std::any_cast<std::string>(a) == std::any_cast<std::string>(b);
    }

    if (a.type() == typeid(bool) && b.type() == typeid(bool))
    {
        return std::any_cast<bool>(a) == std::any_cast<bool>(b);
    }

    return false;
}

void Interpreter::checkNumberOperand(Token op, std::any operand)
{
    if (operand.type() == typeid(double))
    {
        return;
    }
    throw RuntimeError(op, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(Token op, std::any left, std::any right)
{
    if (left.type() == typeid(double) && right.type() == typeid(double))
    {
        return;
    }
    throw RuntimeError(op, "Operands must be numbers.");
}

std::string Interpreter::stringify(std::any object)
{
    if (object.type() == typeid(nullptr))
        return "nil";

    if (object.type() == typeid(double))
    {
        std::string text = std::to_string(std::any_cast<double>(object));
        if (text.find('.') != std::string::npos)
        {
            text.erase(text.find_last_not_of('0') + 1, std::string::npos);
            text.erase(text.find_last_not_of('.') + 1, std::string::npos);
        }
        return text;
    }

    if (object.type() == typeid(std::string))
    {
        return std::any_cast<std::string>(object);
    }

    if (object.type() == typeid(bool))
    {
        return std::any_cast<bool>(object) ? "true" : "false";
    }

    return "Unknown value";
}

void Interpreter::execute(std::shared_ptr<Stmt> stmt)
{
    stmt->accept(*this);
}

void Interpreter::executeBlock(std::vector<std::shared_ptr<Stmt>> statements, std::shared_ptr<Environment> environment)
{
    std::shared_ptr<Environment> previous = this->environment;

    try
    {
        this->environment = environment;

        for(std::shared_ptr<Stmt> statement : statements)
        {
            execute(statement);
        }
    }
    catch(...)
    {
        this->environment = previous;
        throw;
    }
    this->environment = previous;
}