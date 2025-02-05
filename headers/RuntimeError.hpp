#ifndef RUNTIME_ERROR_HPP
#define RUNTIME_ERROR_HPP

#include <stdexcept>
#include "Token.hpp"

class RuntimeError: public std::runtime_error {
public:
  const Token& token;

  RuntimeError(const Token& token, std::string_view message)
    : std::runtime_error{message.data()}, token{token}
  {}
};

#endif