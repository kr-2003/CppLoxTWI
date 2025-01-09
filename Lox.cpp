#include <iostream>
#include <string>
#include <fstream>
#include "headers/Errors.hpp"
#include "headers/Lox.hpp"

TWI::Lox::Lox()
{
    hadError = false;
}

void TWI::Lox::run(const char* source)
{
    std::cout << source << std::endl;
}

std::string TWI::Lox::readFile(const
    char* path)
{
    std::ifstream file {path, std::ios::in | std::ios::binary | std::ios::ate};

    if(!file)
    {
        std::cerr << "Could not open file " << path << std::endl;
        exit(74);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string contents(size, '\0');
    file.read(&contents[0], size);

    file.close();

    return contents;
}

void TWI::Lox::runPrompt()
{
    for(;;)
    {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if(line.empty()) break;
        run(line.c_str());
        hadError = false;
    }
}

void TWI::Lox::runFile(const char* path)
{
    std::string contents
        = readFile(path);

    run(contents.c_str());

    if(hadError) 
    {
        exit(65);
    }
}


