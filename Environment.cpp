#include "./headers/Environment.hpp"

#include <iostream>

std::any Environment::get(Token name)
{
    if (values.find(name.lexeme) != values.end())
    {
        if(values[name.lexeme].type() == typeid(std::nullptr_t))
        {
            throw RuntimeError(name, "Unassigned variable '" + name.lexeme + "'.");
        }
        return values[name.lexeme];
    }

    if(enclosing != nullptr) return enclosing->get(name);

    throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

void Environment::define(std::string name, std::any value)
{
    values[name] = value;
}

void Environment::assign(Token name, std::any value)
{
    if (values.find(name.lexeme) != values.end())
    {
        values[name.lexeme] = value;
        return;
    }

    if(enclosing != nullptr)
    {
        enclosing->assign(name, value);
        return;
    }

    throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}