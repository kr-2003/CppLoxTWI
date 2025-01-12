#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <iostream>
#include <string>

inline bool hadError = false;

inline static void report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
    hadError = true;
}

inline void error(int line, std::string message)
{
    report(line, "", message);
}

#endif // ERRORS_HPP