#ifndef PARSER_H
#define PARSER_H

#include "../lexer/tokenizer.h" 

// The Parser class is responsible for parsing the tokens.
class Parser
{
private:
    Tokenizer lexer;

public:
    Parser(Tokenizer lexer) : lexer(lexer) {}

    // Checks if the next token is of the expected kind.
    bool check(Token expected) {
        return lexer.peek().get_type() == expected.get_type();
    }

    bool hard_check(Token expected) {
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
            "Unexpected Token\n Expected:\t" + expected.token_to_string() +
            "\n Found:\t\t" + lexer.peek().token_to_string());
    }

    Token hard_match(Token expected) 
    {
        if (hard_check(expected)) {
            Token token = lexer.peek();
            lexer.next();
            return token;
        }
        
        throw std::invalid_argument(
            "Error: Token of kind " + expected.token_to_string() + " not found");
    }

    void parse_programm(){
        // parse main function.
        hard_match(Token(TokenClass::IDENTIFIER, std::string("integer")));
        hard_match(Token(TokenClass::IDENTIFIER, std::string("function")));
        hard_match(Token(TokenClass::IDENTIFIER, std::string("main")));
        match(Token(TokenClass::LPAR));
        match(Token(TokenClass::RPAR));
        match(Token(TokenClass::LBRACE));
        
        while(check(Token(TokenClass::NEWLINE)))
            match(Token(TokenClass::NEWLINE));

        while (!check(Token(TokenClass::RBRACE)))
            parse_var_def();

        while(check(Token(TokenClass::NEWLINE)))
            match(Token(TokenClass::NEWLINE));
        
        match(Token(TokenClass::RBRACE));
    }

    void parse_var_def(){
        match(Token(TokenClass::IDENTIFIER));
        match(Token(TokenClass::IDENTIFIER));
        match(Token(TokenClass::EQUALS));
        match(Token(TokenClass::IDENTIFIER));
        match(Token(TokenClass::SEMICOLON));
    }
};

#endif