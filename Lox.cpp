#include <iostream>
#include <fstream>
#include "headers/Errors.hpp"
#include "headers/Lox.hpp"
#include "headers/Scanner.hpp"
#include "headers/Parser.hpp"
#include "headers/AstPrinter.hpp"
#include "headers/Interpreter.hpp"

TWI::Lox::Lox()
{
    hadError = false;
}

Interpreter interpreter{};

void TWI::Lox::run(std::string source)
{
    Scanner scanner{source};
    std::vector<Token> tokens = scanner.scanTokens();
    Parser parser{tokens};
    std::vector<std::shared_ptr<Stmt>> statements = parser.parse();

    if(hadError) return;

    interpreter.interpret(statements);
}

std::string TWI::Lox::readFile(std::string path)
{
    std::ifstream file{path, std::ios::in | std::ios::binary | std::ios::ate};

    if (!file)
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
    for (;;)
    {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty())
            break;
        run(line.c_str());
        hadError = false;
    }
}

void TWI::Lox::runFile(std::string path)
{
    std::string contents = readFile(path);

    run(contents.c_str());

    if (hadError)
    {
        exit(65);
    }

    if(hadRuntimeError)
    {
        exit(70);
    }
}
