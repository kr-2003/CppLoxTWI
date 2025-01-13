#ifndef PARSER_HPP
#define PARSER_HPP

#include "TokenType.hpp"
#include "Token.hpp"
#include "Expr.hpp"
#include "Errors.hpp"
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
    std::shared_ptr<Expr> parse();

private:
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();

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
};

#endif // PARSER_HPP
