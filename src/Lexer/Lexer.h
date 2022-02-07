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
    void getTokens();
    void setInputData( std::string && input );

private:
    TN::Token defineToken( const char* token ) const;
    bool isCommand( const std::string& stringToken ) const;
    bool isNumber( std::string& stringToken ) const;
    void calculate( std::list<TN::Token>& tokens );
    void buildExpressionsOrder( std::string& input );

private:
    std::string m_inputData;
};

}



