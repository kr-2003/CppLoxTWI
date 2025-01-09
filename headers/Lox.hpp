#ifndef LOX_HPP
#define LOX_HPP

#include <string>

namespace TWI
{
    class Lox
    {
        public:
            Lox();
            void runFile(const char* path);
            void runPrompt();
            void run(const char* source);

        private:
            std::string readFile(const char* path);
            bool hadError;
    };
}

#endif // LOX_HPP