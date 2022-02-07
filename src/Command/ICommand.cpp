#include "ICommand.h"

namespace CD
{


void ICommand::addArgument( const std::string& value )
{
    m_arguments.emplace_back( value );
}

const std::list<std::string>& ICommand::getArguments() const
{
    return m_arguments;
}

const std::string& ICommand::getResult() const
{
    return m_result;
}

void ICommand::clearArguments()
{
    m_arguments.clear();
}

void ICommand::clearResult()
{
    m_result.clear();
}

void ICommand::clear()
{
    clearArguments();
    clearResult();
}


}