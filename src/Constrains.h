#pragma once
#include <string>
#include <regex>
namespace CS
{
    const std::string QUIT_COMMAND("quit" );
    const std::regex NUMBER_REGEX( "[(-|+)|][0-9]+" );
    const char QUOTES( '"' );
    const char EXPR_START( '(' );
    const char EXPR_END( ')' );

}