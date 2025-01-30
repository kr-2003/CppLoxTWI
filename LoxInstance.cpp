#include "./headers/LoxInstance.hpp"


std::string LoxInstance::toString()
{
    return klass->name + " instance";
}

std::any LoxInstance::get(Token& name)
{
    auto elem = fields.find(name.lexeme);
    if(elem != fields.end())
    {
        return elem->second;
    }

    std::shared_ptr<LoxFunction> method = klass->findMethod(name.lexeme);
    if(method != nullptr) 
    {
        return method;
    }

    throw RuntimeError(name, "Undefined property '" + name.lexeme + "'.");
}


std::any LoxInstance::set(Token& name, std::any value)
{
    fields[name.lexeme] = value;
}