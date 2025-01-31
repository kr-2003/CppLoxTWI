#include "./headers/LoxFunction.hpp"
#include "./headers/Interpreter.hpp"

LoxFunction::LoxFunction(std::shared_ptr<Function> declaration, std::shared_ptr<Environment> closure, bool isInitializer) : declaration {std::move(declaration)}, closure {std::move(closure)}, isInitializer {std::move(isInitializer)} {};

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
        if(isInitializer)
        {
            return closure->getAt(0, "this");
        }
        return returnValue.value;
    }

    if(isInitializer) 
    {
        return closure->getAt(0, "this");
    }
    
    return nullptr;
}

std::shared_ptr<LoxFunction> LoxFunction::bind(std::shared_ptr<LoxInstance> instance)
{
    std::shared_ptr<Environment> environment = std::make_shared<Environment>(closure);
    environment->define("this", instance);
    return std::make_shared<LoxFunction>(declaration, environment, isInitializer);
}