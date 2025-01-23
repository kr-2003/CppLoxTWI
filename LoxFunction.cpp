#include "./headers/LoxFunction.hpp"
#include "./headers/Interpreter.hpp"

LoxFunction::LoxFunction(std::shared_ptr<Function> declaration, std::shared_ptr<Environment> closure) : declaration {std::move(declaration)}, closure {std::move(closure)} {};

int LoxFunction::arity()
{
    return declaration->params.size();
}

std::string LoxFunction::toString()
{
    return "<fn " + declaration->name.lexeme + ">";
}

std::any LoxFunction::call(Interpreter& interpreter, std::vector<std::any> arguments)
{
    auto environment = std::make_shared<Environment>(closure);
    for(int i = 0; i < declaration->params.size(); i++) 
    {
        environment->define(declaration->params[i].lexeme, arguments[i]);
    }
    try {
        interpreter.executeBlock(declaration->body, environment);
    } catch (LoxReturn &returnValue) {
        return returnValue.value;
    }
    
    return nullptr;
}