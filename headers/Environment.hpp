#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <any>
#include <memory>
#include <unordered_map>
#include <string>
#include "Token.hpp"
#include "RuntimeError.hpp"

class Environment
{
private:
    std::unordered_map<std::string, std::any> values;
    std::shared_ptr<Environment> enclosing;

public:
    Environment() : enclosing(nullptr) {}
    Environment(std::shared_ptr<Environment> enclosing) : enclosing(enclosing) {}
    std::any get(Token name);
    void define(std::string name, std::any value);
    void assign(Token name, std::any value);
};

#endif // ENVIRONMENT_HPP