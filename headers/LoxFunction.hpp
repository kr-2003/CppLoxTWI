#ifndef LOXFUNCTION_HPP
#define LOXFUNCTION_HPP

#include <any>
#include <memory>
#include <string>
#include <vector>
#include "LoxCallable.hpp"

class Environment;
class Function;

class LoxFunction : public LoxCallable
{
public:
    std::shared_ptr<Function> declaration;
    std::shared_ptr<Environment> closure;

public:
    LoxFunction(std::shared_ptr<Function> declaration, std::shared_ptr<Environment> closure);
    int arity() override;
    std::string toString() override;
    std::any call(Interpreter& interpreter, std::vector<std::any> arguments) override;
};

#endif // LOXFUNCTION_HPP