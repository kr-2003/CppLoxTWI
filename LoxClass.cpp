#include "./headers/LoxClass.hpp"

std::string LoxClass::toString()
{
    return name;
}

int LoxClass::arity()
{
    return 0;
}

std::any LoxClass::call(Interpreter& interpreter, std::vector<std::any> arguments)
{
    std::shared_ptr<LoxInstance> instance = std::make_shared<LoxInstance>(shared_from_this());
    return instance;
}