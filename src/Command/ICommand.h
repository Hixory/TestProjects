#pragma once
#include <string>
#include <list>
#include <iostream>

namespace CD
{

class ICommand
{
public:
    virtual ~ICommand() = default;
    ICommand() = default;

public:
    virtual const std::string& execute()
    {
        clearResult();
        int result = 0;
        try
        {
            for( const auto& arg : m_arguments )
            {
                calculate( result, arg );
            }

            m_result = std::to_string( result );
        }
        catch( std::logic_error& ex )
        {
            std::cout<<"Wrong argument type for command"<<std::endl;
            return m_result;
        }
        return m_result;
    }
    void addArgument( const std::string& value );
    const std::list<std::string>& getArguments() const;
    const std::string& getResult() const;
    void clearArguments();
    void clearResult();
    void clear();

protected:
    virtual void calculate( int& result, const std::string& arg ) = 0;

protected:
    std::list<std::string> m_arguments;
    std::string m_result;
};

}