#include <iostream>
#include "headers/Lox.hpp"

int main(int argc, char** argv)
{
    TWI::Lox lox;
    
    if(argc > 2)
    {
        std::cerr << "Usage: cppLox [script]" << std::endl;
        return 64;
    }
    else if(argc == 2)
    {
        lox.runFile(argv[1]);
    }
    else
    {
        lox.runPrompt();
    }
    return 0;
}