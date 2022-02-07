#pragma once
#include "src/Lexer/Token.h"
#include "ICommand.h"
#include <set>
#include <list>
#include <iostream>

namespace CD
{


enum class CommandType
{
    ADD = 0,
    SUB,
    MULT,
    CONCAT
};

static const std::unordered_map<std::string, CommandType> COMMAND_TYPES { {"add", CommandType::ADD },
                                                                          {"sub", CommandType::SUB },
                                                                          {"mult", CommandType::MULT },
                                                                          {"concat", CommandType::CONCAT } };

static const std::unordered_map<const char*, CommandType> COMMAND_TOKEN_TYPES { {"add", CommandType::ADD },
                                                                                {"sub", CommandType::SUB },
                                                                                {"mult", CommandType::MULT },
                                                                                {"concat", CommandType::CONCAT } };

template<CommandType type>
class Command: public ICommand
{
};

template<>
class Command<CommandType::ADD> : public ICommand
{
    void calculate( int& result, const std::string& arg ) override
    {
        result += std::stoi( arg );
    }
};

template<>
class Command<CommandType::MULT> : public ICommand
{
    void calculate( int& result, const std::string& arg ) override
    {
        if( m_firstCall )
        {
            result = 1;
            m_firstCall = false;
        }
        result *= stoi( arg );
    }

private:
    bool m_firstCall = true;
};

template<>
class Command<CommandType::SUB> : public ICommand
{
    void calculate( int& result, const std::string& arg ) override
    {
        if( m_firstCall )
        {
            result = stoi( arg );
            m_firstCall= false;
        }
        else
        {
            result -= stoi( arg );
        }
    }

private:
    bool m_firstCall = true;
};

template<>
class Command<CommandType::CONCAT> : public ICommand
{
    void calculate( int& result, const std::string& arg ) override {};

    const std::string& execute() override
    {
        clearResult();

        for( auto& arg : m_arguments )
        {
            m_result.append( arg );
        }
        return m_result;
    }
};


std::unique_ptr<ICommand> createCommand( const std::string& commandName )
{
    auto commandType = CD::COMMAND_TYPES.at( commandName );
    switch( commandType )
    {
        case CommandType::ADD:
        {
            return std::make_unique<CD::Command<CommandType::ADD>>();
        }
        case CommandType::SUB:
        {
            return std::make_unique<CD::Command<CommandType::SUB>>();
        }
        case CommandType::MULT:
        {
            return std::make_unique<CD::Command<CommandType::MULT>>();
        }
        case CommandType::CONCAT:
        {
            return std::make_unique<CD::Command<CommandType::CONCAT>>();
        }
        default:
        {
            std::cout << "Syntax is broken. Unknown command type" << std::endl;
            throw std::logic_error("");
        }
    }
}


}



