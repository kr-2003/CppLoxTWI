#include "./headers/Parser.hpp"

Parser::Parser(std::vector<Token> tokens) : tokens{tokens} {}

std::shared_ptr<Expr> Parser::parse()
{
    try
    {
        return expression();
    }
    catch (ParseError error)
    {
        return nullptr;
    }
}

std::shared_ptr<Expr> Parser::expression()
{
    return equality();
}

std::shared_ptr<Expr> Parser::equality()
{
    std::shared_ptr<Expr> expr = comparison();

    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL))
    {
        Token opr = previous();
        std::shared_ptr<Expr> right = comparison();
        expr = std::make_shared<Binary>(expr, std::move(opr), right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison()
{
    std::shared_ptr<Expr> expr = term();

    while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL))
    {
        Token opr = previous();
        std::shared_ptr<Expr> right = term();
        expr = std::make_shared<Binary>(expr, std::move(opr), right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::term()
{
    std::shared_ptr<Expr> expr = factor();

    while (match(TokenType::PLUS, TokenType::MINUS))
    {
        Token opr = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_shared<Binary>(expr, std::move(opr), right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor()
{
    std::shared_ptr<Expr> expr = unary();

    while (match(TokenType::STAR, TokenType::SLASH))
    {
        Token opr = previous();
        std::shared_ptr<Expr> right = unary();
        expr = std::make_shared<Binary>(expr, std::move(opr), right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::unary()
{
    if (match(TokenType::BANG, TokenType::MINUS))
    {
        Token opr = previous();
        std::shared_ptr<Expr> right = unary();
        return std::make_shared<Unary>(opr, right);
    }

    return primary();
}

std::shared_ptr<Expr> Parser::primary()
{
    if (match(TokenType::FALSE))
        return std::make_shared<Literal>(false);
    if (match(TokenType::TRUE))
        return std::make_shared<Literal>(true);
    if (match(TokenType::NIL))
        return std::make_shared<Literal>(nullptr);

    if (match(TokenType::NUMBER, TokenType::STRING))
    {
        return std::make_shared<Literal>(previous().literal);
    }

    if (match(TokenType::LEFT_PAREN))
    {
        std::shared_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<Grouping>(expr);
    }

    throw error(peek(), "Expect expression.");
}

Token Parser::consume(TokenType type, std::string message)
{
    if (check(type))
        return advance();
    throw error(peek(), message);
}

Parser::ParseError Parser::error(Token token, std::string message)
{
    if (token.type == TokenType::EoF)
    {
        report(token.line, " at end", message);
    }
    else
    {
        report(token.line, " at " + token.lexeme + "'", message);
    }
    return ParseError(message);
}

template <class... T>
bool Parser::match(T... type)
{
    assert((... && std::is_same_v<T, TokenType>));

    if ((... || check(type)))
    {
        advance();
        return true;
    }

    return false;
}

bool Parser::check(TokenType type)
{
    if (isAtEnd())
        return false;
    return peek().type == type;
}

Token Parser::advance()
{
    if (!isAtEnd())
        current++;
    return previous();
}

bool Parser::isAtEnd()
{
    return peek().type == TokenType::EoF;
}

Token Parser::peek()
{
    return tokens[current];
}

Token Parser::previous()
{
    return tokens[current - 1];
}

void Parser::synchronize()
{
    advance();

    while (!isAtEnd())
    {
        if (previous().type == TokenType::SEMICOLON)
            return;

        switch (peek().type)
        {
        case TokenType::CLASS:
        case TokenType::FUN:
        case TokenType::VAR:
        case TokenType::FOR:
        case TokenType::IF:
        case TokenType::WHILE:
        case TokenType::PRINT:
        case TokenType::RETURN:
            return;
        }

        advance();
    }
}
