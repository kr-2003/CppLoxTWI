#ifndef LOX_HPP
#define LOX_HPP

#include <string>

namespace TWI
{
    class Lox
    {
        public:
            Lox();
            void runFile(std::string path);
            void runPrompt();
            void run(std::string source);

        private:
            std::string readFile(std::string path);
            bool hadError;
    };
}

#endif // LOX_HPP