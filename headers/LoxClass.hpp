#ifndef LOXCLASS_HPP
#define LOXCLASS_HPP

#include "LoxCallable.hpp"
#include "LoxInstance.hpp"
#include <string>
#include <utility>
#include <any>

class LoxClass : public LoxCallable, public std::enable_shared_from_this<LoxClass> 
{
public:
    std::string name;

public:
    LoxClass(std::string name) : name {std::move(name)} {}
    std::string toString() override;
    int arity() override;
    std::any call(Interpreter& interpreter, std::vector<std::any> arguments) override;
};

#endif // LOXCLASS_HPP