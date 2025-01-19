#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "../lexer/tokenizer.h"

// The Parser class is responsible for parsing the tokens.
class Parser
{
private:
    Tokenizer lexer;

public:
    Parser(Tokenizer lexer) : lexer(lexer) {}

    // Checks if the next (at most) two tokens are of the expected type.
    bool check(std::vector<Token> expected)
    {
        bool is_expected = true;
        for (int i = 0; i < expected.size(); i++)
        {
            if (lexer.peek()[i].get_type() != expected[i].get_type())
                return false;
        }
        return true;
    }

    // checks if the next (at most) two tokens has type and value.
    bool hard_check(std::vector<Token> expected)
    {
        if (expected.size() == 0)
            return false;

        std::vector<Token> tokens = lexer.peek();
        for (int i = 0; i < expected.size(); i++) {
            if (!(tokens[i] == expected[i])) 
                return false;
        }
        return true;
    }

    // Consumes the next token if it is of the expected kind.
    Token match(std::vector<Token> expected)
    {
        if (check({expected}))
        {
            Token token = lexer.peek()[0];
            lexer.next();
            return token;
        }

        throw std::invalid_argument(
            "Unexpected Token\n Expected:\t" + expected[0].token_to_string() +
            "\n Found:\t\t" + lexer.peek()[0].token_to_string());
    }

    Token hard_match(Token expected)
    {
        if (hard_check({expected}))
        {
            Token token = lexer.peek()[0];
            lexer.next();
            return token;
        }

        throw std::invalid_argument(
            "Unexpected Token\n Expected:\t" + expected.token_to_string() +
            "\n Found:\t\t" + lexer.peek()[0].token_to_string());
    }

    void parse_programm()
    {
        // parse main function.
        hard_match({Token(TokenClass::TYPE, std::string("integer"))});

        hard_match({Token(TokenClass::IDENTIFIER, std::string("function"))});
        hard_match({Token(TokenClass::IDENTIFIER, std::string("main"))});
        match({Token(TokenClass::LPAR)});
        match({Token(TokenClass::RPAR)});
        match({Token(TokenClass::LBRACE)});

        while (check({Token(TokenClass::NEWLINE)}))
            match({Token(TokenClass::NEWLINE)});

        parse_function_body();

        while (check({Token(TokenClass::NEWLINE)}))
            match({Token(TokenClass::NEWLINE)});

        match({Token(TokenClass::RBRACE)});
    }

    void parse_function_body()
    {
        while (check({Token(TokenClass::TYPE)}))
            parse_var_def();
    }

    void parse_var_def()
    {
        match({Token(TokenClass::TYPE)});
        match({Token(TokenClass::IDENTIFIER)});
        match({Token(TokenClass::EQUALS)});
        match({Token(TokenClass::IDENTIFIER)});
        match({Token(TokenClass::SEMICOLON)});
    }

    void parse_statement()
    {
    }
};

#endif