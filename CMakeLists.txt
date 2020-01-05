cmake_minimum_required(VERSION 3.15)
project(Flight-Simulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Flight-Simulator main.cpp
                Command.cpp Command.h Minus.cpp Plus.cpp UMinus.cpp UPlus.cpp Div.cpp Mul.cpp Token.cpp Ex1.h
        Expression.h Interpreter.cpp Token.h UnaryOperator.cpp BinaryOperator.cpp Value.cpp Variable.cpp
                Lexer.cpp Parser.cpp Command.h Command.cpp Lexer.h Parser.h BooleanExpression.cpp)