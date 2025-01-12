#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "TokenType.hpp"
#include "Token.hpp"

class Scanner
{
private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;
    std::unordered_map<std::string, TokenType> keywords;

public:
    Scanner();
    Scanner(std::string source);
    std::vector<Token> scanTokens();

private:
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::any literal);
    bool match(char expected);
    char peek();
    void _string();
    bool isDigit(char c);
    void number();
    char peekNext();
    bool isAlpha(char c);
    bool isAlphanumeric(char c);
    void identifier();
    void initialiseKeywords();
};

#endif // SCANNER_HPP