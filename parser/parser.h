#ifndef PARSER_H
#define PARSER_H

#include "lexer/tokenizer.h"

// The Parser class is responsible for parsing the tokens.
class Parser
{
private:
    Tokenizer lexer;

public:
    Parser(Tokenizer lexer) : lexer(lexer) {

    }

    // Checks if the next token is of the expected kind.
    bool check(Token expected) {
        return lexer.peek() == expected;
    }

    // Consumes the next token if it is of the expected kind.
    Token match(Token expected) 
    {
        if (check(expected)) {
            Token token = lexer.peek();
            lexer.next();
            return token;
        }
        
        throw std::invalid_argument(
            "Error: Token of kind " + expected.token_to_string() + " not found");
    }

    void parse_programm(){
        
    }
};

#endif