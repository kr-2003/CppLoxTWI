#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <any>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include "Token.hpp"
#include "RuntimeError.hpp"

class Environment : public std::enable_shared_from_this<Environment>
{
private:
    std::unordered_map<std::string, std::any> values;

public:
    std::shared_ptr<Environment> enclosing;

public:
    Environment() : enclosing(nullptr) {}
    Environment(std::shared_ptr<Environment> enclosing) : enclosing(enclosing) {}
    std::any get(Token name);
    void define(std::string name, std::any value);
    void assign(Token name, std::any value);
    std::any getAt(int distance, std::string name);
    std::shared_ptr<Environment> ancestor(int distance);
    void assignAt(int distance, Token& name, std::any value);
};

#endif // ENVIRONMENT_HPP