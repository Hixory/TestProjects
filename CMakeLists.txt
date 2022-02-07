cmake_minimum_required(VERSION 3.21)

project(Interpreter VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Interpreter src/main.cpp)

add_library(lexer src/Lexer/Lexer.cpp
            src/Lexer/Token.h
            src/Command/Command.cpp
            src/Command/Command.h
            src/Command/ICommand.h src/Command/ICommand.cpp)
target_include_directories(lexer
        PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_include_directories(Interpreter
        PUBLIC
            "${PROJECT_BINARY_DIR}"
            "${PROJECT_SOURCE_DIR}"
)

target_link_libraries( Interpreter lexer )