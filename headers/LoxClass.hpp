#ifndef LOXCLASS_HPP
#define LOXCLASS_HPP

#include "LoxCallable.hpp"
#include "LoxInstance.hpp"
#include "LoxFunction.hpp"
#include <string>
#include <utility>
#include <any>
#include <map>

class LoxFunction;

class LoxClass : public LoxCallable, public std::enable_shared_from_this<LoxClass> 
{
public:
    std::string name;
    std::shared_ptr<LoxClass> superclass;

private:
    std::map<std::string, std::shared_ptr<LoxFunction>> methods;

public:
    LoxClass(std::string name, std::shared_ptr<LoxClass> superclass, std::map<std::string, std::shared_ptr<LoxFunction>> methods) : name {std::move(name)}, superclass {std::move(superclass)}, methods {std::move(methods)} {}
    std::string toString() override;
    int arity() override;
    std::any call(Interpreter& interpreter, std::vector<std::any> arguments) override;
    std::shared_ptr<LoxFunction> findMethod(std::string name);
};

#endif // LOXCLASS_HPP