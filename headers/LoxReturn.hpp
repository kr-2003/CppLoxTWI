#ifndef LOXRETURN_HPP
#define LOXRETURN_HPP

#include <any>

class LoxReturn
{
public:
    const std::any value;
public:
    LoxReturn(std::any value) : value(value) {}
};

#endif // LOXRETURN_HPP