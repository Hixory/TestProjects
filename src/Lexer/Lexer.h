#pragma once

#include <list>
#include "Token.h"

namespace LR
{

class Lexer
{
public:
    Lexer() = default;
    Lexer( const Lexer & ) = delete;
    Lexer &operator=(const Lexer &) = delete;
    ~Lexer() = default;

public:
    std::list<TN::Token> getTokens();
    void setInputData( std::string && input );

private:
    TN::Token defineToken( const char* token );
    bool isCommand( const char* token );
    bool isNumber( std::string& stringToken );
    void calculate( std::list<TN::Token>& tokens );
    void buildExpressionsOrder( std::string& input );

private:
    std::string m_inputData;
};

}



