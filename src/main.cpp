#include <iostream>
#include <fstream>
#include <vector>
#include <locale>

#pragma GCC diagnostic warning "-Wunused"
#define STR_IT(X) #X 

using namespace std;

std::string configfile = "configs/test.conf";

// symbol definitions.
enum TOKENS {
    COLON,
    L_BRACE,
    R_BRACE,
    POUND,
    COMMA,
    INDENT,
    OBJ,
    ARG,
    VAL
};

vector<std::string> tokenstr =
{
    STR_IT(COLON),
    STR_IT(L_BRACE),
    STR_IT(R_BRACE),
    STR_IT(POUND),
    STR_IT(COMMA),
    STR_IT(INDENT),
    STR_IT(OBJ),
    STR_IT(ARG),
    STR_IT(VAL)
};

/*
    the Lexer creates a array of tokens.
    each might have a value, and they contain
    which token they are (like COLON for ':')
*/
typedef struct
{
    std::string value;
    TOKENS token;
} token_t;

class Lexer
{
public:
    Lexer(std::string);
    char get();
    char peek();
    vector<token_t> lex();
    token_t get_token();

private:

    vector<token_t> tokens;
    std::ifstream infile;
};

Lexer::Lexer(std::string file)
{
    this->infile = std::ifstream(file);
}

vector<token_t> Lexer::lex()
{
    // token_t test_token = {"TEST", COLON};
    // this->tokens.push_back(test_token);
    token_t current_token;

    while(this->infile.good())
    {
        // start of object ?
        if(this->peek() == '#')
        {
            std::cout << "WELL A COMMENT\n";
            while(this->peek() != '\n')
            {
                this->get();
            }
        }
        else if(std::isalpha(this->peek()) && !std::isspace(this->peek()))
        {
            current_token.value = "";
            while(this->peek() != ':')
            {
                if(!std::isspace(this->peek()))
                {
                    current_token.value += this->get();
                }
                else
                {
                    this->get();
                }
            }
            current_token.token = OBJ;
            this->tokens.push_back(current_token);
        }
        this->get();
    }

    return this->tokens;
}

char Lexer::get()
{
    return (char)this->infile.get();
}

char Lexer::peek()
{
    return (char)this->infile.peek();
}

int main(void)
{
    Lexer lexer = Lexer(configfile);
    vector<token_t> tokens = lexer.lex();

    // for(size_t i = 0; i < tokens.size(); i++)
    // {
    //     std::cout << tokens.value << ":" << tokens.token << std::endl;
    // }

    for(auto token: tokens)
    {
        std::cout << token.value << ":" << tokenstr[token.token] << std::endl;
    }

    return 0;
}