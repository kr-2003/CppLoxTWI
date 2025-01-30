#ifndef PARSER_HPP
#define PARSER_HPP

#include "TokenType.hpp"
#include "Token.hpp"
#include "Expr.hpp"
#include "Errors.hpp"
#include "Stmt.hpp"
#include <vector>
#include <memory>
#include <utility>
#include <stdexcept>
#include <string>
#include <cassert>

class Parser
{
    struct ParseError : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

private:
    std::vector<Token> tokens;
    int current = 0;

public:
    Parser(std::vector<Token> tokens);
    std::vector<std::shared_ptr<Stmt>> parse();

private:
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();
    std::shared_ptr<Expr> assignment();

    Token consume(TokenType type, std::string message);
    ParseError error(Token token, std::string message);

    template <class... T>
    bool match(T... type);

    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    void synchronize();
    std::shared_ptr<Stmt> statement();
    std::shared_ptr<Stmt> printStatement();
    std::shared_ptr<Stmt> expressionStatement();
    std::shared_ptr<Stmt> declaration();
    std::shared_ptr<Stmt> varDeclaration();
    std::vector<std::shared_ptr<Stmt>> block();
    std::shared_ptr<Stmt> ifStatement();
    std::shared_ptr<Stmt> whileStatement();
    std::shared_ptr<Stmt> forStatement();
    std::shared_ptr<Expr> _or();
    std::shared_ptr<Expr> _and();
    std::shared_ptr<Expr> call();
    std::shared_ptr<Expr> finishCall(std::shared_ptr<Expr> callee);
    std::shared_ptr<Function> function(std::string kind);
    std::shared_ptr<Stmt> returnStatement();
    std::shared_ptr<Stmt> classDeclaration();
};

#endif // PARSER_HPP
