cmake_minimum_required(VERSION 3.15)
project(Flight-Simulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Flight-Simulator main.cpp
                Command.cpp Command.h Ex1/Minus.cpp Ex1/Plus.cpp Ex1/UMinus.cpp Ex1/UPlus.cpp Ex1/Div.cpp Ex1/Mul.cpp Token.cpp Ex1/Ex1.h
        Ex1/Expression.h Ex1/Interpreter.cpp Token.h Ex1/UnaryOperator.cpp Ex1/BinaryOperator.cpp Ex1/Value.cpp Ex1/Variable.cpp
                Lexer.cpp Parser.cpp Command.h Command.cpp Lexer.h Parser.h Ex1/BooleanExpression.cpp)