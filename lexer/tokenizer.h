#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "scanner.h"
#include "token.h"
#include <iostream>

class Tokenizer
{
private:
  Scanner scanner;
  std::optional<Token> buffer;

public:
  Tokenizer(Scanner scanner) : scanner(scanner), buffer() {}

  Token peek()
  {
    if (!buffer.has_value())
      buffer = next();
    return buffer.value();
  }

  Scanner &get_scanner() { return scanner; }

  bool is_keyword(std::string token_value)
  {
    if (token_value == "if" || token_value == "while" || token_value == "else")
      return true;
    
    return false;
  }

  bool is_type(std::string token_value)
  {
    if (token_value == "integer" || token_value == "float" || token_value == "double" || token_value == "char" || token_value == "string")
      return true;
    return false;
  }

  // Reads and returns the next token.
  std::optional<Token> next()
  {
    if (buffer.has_value())
    {
      Token t = buffer.value();
      buffer.reset();
      return t;
    }

    char c = scanner.next();

    if (c == '\n')
      return Token(TokenClass::NEWLINE);
    if (std::isspace(c))
      return next();
    if (c == '+')
      return Token(TokenClass::PLUS);
    if (c == '-')
      return Token(TokenClass::MINUS);
    if (c == '(')
      return Token(TokenClass::LPAR);
    if (c == ')')
      return Token(TokenClass::RPAR);
    if (c == '{')
      return Token(TokenClass::LBRACE);
    if (c == '}')
      return Token(TokenClass::RBRACE);
    if (c == ',')
      return Token(TokenClass::COMMA);
    if (c == '=')
      return Token(TokenClass::EQUALS);
    if (c == ';')
      return Token(TokenClass::SEMICOLON);
    if (std::isalpha(c))
    {
      std::string name = std::string(1, c);
      std::optional<char> pc = scanner.peek();
      while (pc.has_value())
      {
        bool is_underscore = pc.value() == '_';
        bool isalpha_or_digit = std::isalpha(pc.value()) || std::isdigit(pc.value());
        if (!(is_underscore || isalpha_or_digit))
        {
          break;
        }
        name.push_back(pc.value());
        scanner.next();
        pc = scanner.peek();
      }

      if (is_keyword(name))
        return Token(TokenClass::KEYWORD, name);
      if (is_type(name))
        return Token(TokenClass::TYPE, name);

      return Token(TokenClass::IDENTIFIER, name);
    }

    if (std::isdigit(c))
    {
      std::string digits(1, c);
      std::optional<char> pc = scanner.peek();
      while (pc.has_value() && std::isdigit(pc.value()))
      {
        digits.push_back(pc.value());
        scanner.next();
        pc = scanner.peek();
      }

      int value = std::stoi(digits);
      return Token(TokenClass::IDENTIFIER, value);
    }

    return std::nullopt;
  }
};

#endif
