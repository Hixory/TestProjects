#include <cstring>
#include <iostream>
#include <regex>
#include "Lexer.h"
#include "src/Command/Command.h"
#include "src/Constrains.h"

namespace LR
{
    void Lexer::setInputData( std::string && input )
    {
        m_inputData = std::move( input );
    }

    bool Lexer::isCommand( const std::string& stringToken ) const
    {
        if( CD::COMMAND_TYPES.find( stringToken ) != CD::COMMAND_TYPES.end() )
            return true;

        return false;
    }

    bool Lexer::isNumber( std::string& stringToken ) const
    {
        if( stringToken[0] == QUOTES && stringToken[stringToken.size() - 1] == QUOTES )
        {
            stringToken = stringToken.substr(1, stringToken.size() - 2 );
        }

        return std::regex_match( stringToken, NUMBER_REGEX );
    }

    TN::Token Lexer:: defineToken( const char* token ) const
    {
        std::string strToken( token );
        if( isCommand( strToken ) )
        {
            return {TN::TokenIdentity::Command, strToken };
        }
        else if( isNumber( strToken ) )
        {
            return {TN::TokenIdentity::Number, strToken };
        }
        else
        {
            return {TN::TokenIdentity::String, strToken };
        }
    }

    void Lexer::buildExpressionsOrder( std::string& input )
    {
        auto startExpr = input.find( EXPR_START );
        if( startExpr !=  std::string::npos )
        {
            auto endExpr = input.rfind( EXPR_END );
            if( endExpr !=  std::string::npos )
            {
                std::string buffer = input.substr( startExpr + 1, endExpr - startExpr - 1 );
                input.erase( startExpr, buffer.size() + 2 );
                buffer.append( " " );
                buffer.append( input );
                input = std::move( buffer );
                buildExpressionsOrder( input );
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }

    void Lexer::getTokens()
    {
        buildExpressionsOrder( m_inputData );
        std::list<TN::Token> result;

        auto charData = m_inputData.data();

        auto token = std::strtok( charData, " " );
        while( token )
        {
            auto tokenType = defineToken( token );
            result.emplace_back( std::move( tokenType ) );
            token = std::strtok( nullptr, " " );
        }
        calculate( result );
    }

    void Lexer::calculate( std::list<TN::Token>& tokens )
    {
        std::map<int, std::unique_ptr<CD::ICommand>> commands;
        int level = -1;
        for( const auto& [ type, value ] : tokens )
        {
            switch( type )
            {
                case TN::TokenIdentity::Command:
                {
                    level++;
                    commands.emplace( level, std::move( CD::createCommand( value ) ) );
                    break;
                }
                case TN::TokenIdentity::Number:
                case TN::TokenIdentity::String:
                {
                    try
                    {
                        commands.at( level )->addArgument( value );
                    }
                    catch( std::out_of_range& ex )
                    {
                        throw std::logic_error( "Wrong syntax" );
                    }

                    break;
                }
                default:
                {
                    throw std::logic_error( "Corrupted data on input" );
                }
            }
        }

        std::string result;
        auto it = commands.begin();
        while( it != commands.end() )
        {
            if( !result.empty() )
            {
                it->second->addArgument( result );
            }
            result = it->second->execute();
            it++;
        }

        if( result.empty() )
        {
            throw std::logic_error( "Wrong syntax" );
        }

        std::cout<<"Result: "<<result<<std::endl;
    }


}