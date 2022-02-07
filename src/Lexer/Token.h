#pragma once
#include <string>
#include <unordered_map>

namespace TN
{

enum class TokenIdentity
{
    Command = 0,
    Number,
    String
};


struct Token
{
    TokenIdentity type;
    std::string value;
};

}