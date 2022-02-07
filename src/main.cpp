#include <iostream>
#include <string>
#include "Constrains.h"
#include "Lexer/Lexer.h"


int main()
{
    static LR::Lexer lexer;
    std::string inputData;
    std::cout<<"Dummy Interpreter 0.1"<<std::endl;
    while( true )
    {
        try
        {
            std::getline( std::cin, inputData );

            if( inputData == QUIT_COMMAND )
            {
                std::cout<<"Stop"<<std::endl;
                break;
            }
            lexer.setInputData( std::move( inputData ) );
            lexer.getTokens();
            continue;
        }
        catch( std::logic_error& ex )
        {
            std::cout<<"Error: "<<ex.what()<<std::endl;
            continue;
        }

    }
    return 0;
}
