#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "RuntimeError.hpp"
#include <iostream>
#include <string>

inline bool hadError = false;
inline bool hadRuntimeError = false;

inline static void report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
    hadError = true;
}

inline void error(const Token& token, std::string message) {
  if (token.type == TokenType::EoF) {
    report(token.line, " at end", message);
  } else {
    report(token.line, " at '" + token.lexeme + "'", message);
  }
}


inline void error(int line, std::string message)
{
    report(line, "", message);
}

inline void runtimeError(RuntimeError error)
{
    std::cerr << error.what() << "\n[line " << error.token.line << "]\n";
    hadRuntimeError = true;
}

#endif // ERRORS_HPP