#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <optional>
#include <any>
#include <format>

enum TokenClass
{
  IDENTIFIER,
  KEYWORD,
  OPERATOR,
  PLUS,
  MINUS,
  NEWLINE,
  LPAR,
  RPAR,
  LBRACE,
  RBRACE,
  SEMICOLON,
  COMMA,
  EQUALS,
};

class Token
{
private:
  enum TokenClass type;
  std::optional<std::any> value;

public:
  TokenClass get_type() { return type; }

  // Checks Equality of two tokens.
  bool operator==(const Token &other) const
  {
    if (!this->value.has_value())
    {
      if (!other.value.has_value())
        return this->type == other.type;
      return false;
    }

    TokenClass this_type = this->type;
    TokenClass other_type = other.type;
    std::any this_value = this->value.value();
    std::any other_value = other.value.value();
    
    bool same_value_type = this_value.type() == other_value.type();
    
    // If the types are the same, compare the values.
    if (this_type == other_type) {
      if (this_value.type() == typeid(int) && other_value.type() == typeid(int))
        return std::any_cast<int>(this_value) == std::any_cast<int>(other_value);
      else if (this_value.type() == typeid(float) && other_value.type() == typeid(float))
        return std::any_cast<float>(this_value) == std::any_cast<float>(other_value);
      else if (this_value.type() == typeid(double) && other_value.type() == typeid(double))
        return std::any_cast<double>(this_value) == std::any_cast<double>(other_value);
      else if (this_value.type() == typeid(char) && other_value.type() == typeid(char))
        return std::any_cast<char>(this_value) == std::any_cast<char>(other_value);
      else if (this_value.type() == typeid(std::string) && other_value.type() == typeid(std::string))
        return std::any_cast<std::string>(this_value) == std::any_cast<std::string>(other_value);
    }

    return false;
  }

  Token(TokenClass token_type, std::optional<std::any> token_value = std::nullopt)
  {
    type = token_type;
    if (token_value.has_value())
      value = token_value.value();
  }



  std::string token_to_string()
  {
    const std::string nameTT[] = {
      "IDENTIFIER", "KEYWORD", "OPERATOR", 
      "PLUS", "MINUS", "NEWLINE",
      "LPAR", "RPAR", "LBRACE", "RBRACE",
      "SEMICOLON", "COMMA", "EQUALS"
    };
    const std::string tokenclass = nameTT[static_cast<int>(type)];

    std::string val = "";
    if (value.has_value())
    {
      if (value->type() == typeid(int))
        val = std::to_string(std::any_cast<int>(*value));
      else if (value->type() == typeid(double))
        val = std::to_string(std::any_cast<double>(*value));
      else if (value->type() == typeid(std::string))
        val = std::any_cast<std::string>(*value);
    }

    return tokenclass + (!val.empty() ? "(" + val + ")" : "");
  }
};

#endif
