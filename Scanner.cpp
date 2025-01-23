#include "./headers/Scanner.hpp"
#include "./headers/Errors.hpp"

Scanner::Scanner() : source{""} 
{
    initialiseKeywords();
}

Scanner::Scanner(std::string source) : source{source} 
{
    initialiseKeywords();
}

std::vector<Token> Scanner::scanTokens()
{
    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    tokens.push_back(Token(TokenType::EoF, "", NULL, line));

    return tokens;
}

bool Scanner::isAtEnd()
{
    return current >= source.length();
}

void Scanner::scanToken()
{
    char c = advance();
    switch (c)
    {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case '.':
        addToken(TokenType::DOT);
        break;
    case '-':
        addToken(TokenType::MINUS);
        break;
    case '+':
        addToken(TokenType::PLUS);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if(match('/'))
        {
            while(peek() != '\n' && !isAtEnd())
            {
                advance();
            }
        }
        else
        {
            addToken(TokenType::SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        line++;
        break;
    case '"':
        _string();
        break;

    default:
        if(isDigit(c))
        {
            number();
        }
        else if(isAlpha(c))
        {
            identifier();
        }
        else 
        {
            error(line, "Unexpected character.");
        }
        break;
    }
}

char Scanner::advance()
{
    return source[current++];
}

void Scanner::addToken(TokenType type)
{
    addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal)
{
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected)
{
    if(isAtEnd())
    {
        return false;
    }
    if(source[current] != expected)
    {
        return false;
    }

    current++;
    return true;
}

char Scanner::peek()
{
    if(isAtEnd())
    {
        return '\0';
    }
    return source[current];
}

void Scanner::_string()
{
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n')
        {
            line++;
        }
        advance();
    }

    if(isAtEnd())
    {
        error(line, "Unterminated string.");
        return;
    }

    advance();

    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

void Scanner::number()
{
    while(isDigit(peek()))
    {
        advance();
    }

    if(peek() == '.' && isDigit(peekNext()))
    {
        advance();
        while(isDigit(peek()))
        {
            advance();
        }
    }

    addToken(TokenType::NUMBER, std::stod(source.substr(start, current - start)));
}

char Scanner::peekNext()
{
    if(current + 1 >= source.length())
    {
        return '\0';
    }

    return source[current + 1];
}

void Scanner::identifier()
{
    while(isAlphanumeric(peek())) 
    {
        advance();
    }

    std::string text = source.substr(start, current - start);
    TokenType type = keywords.count(text) ? keywords[text] : TokenType::IDENTIFIER;
    if(type == TokenType::IDENTIFIER)
    {
        addToken(TokenType::IDENTIFIER);
    }
    else
    {
        addToken(type);
    }
}

bool Scanner::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphanumeric(char c) 
{
    return isAlpha(c) || isDigit(c);
}

void Scanner::initialiseKeywords()
{
    keywords["and"] = TokenType::AND;
    keywords["class"] = TokenType::CLASS;
    keywords["else"] = TokenType::ELSE;
    keywords["false"] = TokenType::FALSE;
    keywords["for"] = TokenType::FOR;
    keywords["fun"] = TokenType::FUN;
    keywords["if"] = TokenType::IF;
    keywords["nil"] = TokenType::NIL;
    keywords["or"] = TokenType::OR;
    keywords["print"] = TokenType::PRINT;
    keywords["return"] = TokenType::RETURN;
    keywords["super"] = TokenType::SUPER;
    keywords["this"] = TokenType::THIS;
    keywords["true"] = TokenType::TRUE;
    keywords["var"] = TokenType::VAR;
    keywords["while"] = TokenType::WHILE;
}