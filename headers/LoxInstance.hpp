#ifndef LOXINSTANCE_HPP
#define LOXINSTANCE_HPP


#include "LoxClass.hpp"
#include "Token.hpp"
#include "Errors.hpp"

#include <any>
#include <map>
#include <memory>
#include <string>
#include <utility>

class LoxClass;
class Token;

class LoxInstance: public std::enable_shared_from_this<LoxInstance> 
{
public:
  std::shared_ptr<LoxClass> klass;
  std::map<std::string, std::any> fields;

public:
  LoxInstance(std::shared_ptr<LoxClass> klass) : klass {std::move(klass)} {}
  std::string toString();
  std::any get(Token& name);
  std::any set(Token& name, std::any value);
};


#endif