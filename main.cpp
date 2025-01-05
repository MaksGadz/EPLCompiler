#include "lexer/token.h"
#include "lexer/tokenizer.h"
#include "lexer/scanner.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::string read_file(std::string filename)
{
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

Tokenizer init_tokenizer(std::string filename) 
{
    std::string buffer = read_file(filename);
    Scanner scanner(buffer);
    Tokenizer tokenizer(scanner);
    return tokenizer;
}

std::vector<Token> tokenize_file(Tokenizer tokenizer)
{
    std::vector<Token> tokens;
    std::optional<Token> token;
    while(!tokenizer.get_scanner().stream_empty())
    {
        token = tokenizer.next();
        tokens.push_back(token.value());
    }
    return tokens;
}

int main(int argc, char* argv[])
{   
    // Check if the filename is provided.
    if (argc != 2) {
        std::cout << "Usage: ./main <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    // Initialize the tokenizer.
    Tokenizer tokenizer = init_tokenizer(filename);
    
    // Tokenize the file.
    std::vector<Token> tokens = tokenize_file(tokenizer);

    

    std::cout << std::endl << std::endl;
}