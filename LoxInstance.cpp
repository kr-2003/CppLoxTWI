#include "./headers/LoxInstance.hpp"


std::string LoxInstance::toString()
{
    return klass->name + " instance";
}