//
// Created by shani on 08/11/2019.
//

#ifndef UNTITLED_TOKEN_H
#define UNTITLED_TOKEN_H

#include <string>
using namespace std;

enum typeToken {Operator, Number, LeftBrace, RightBrace};
//enum priority {Braces=20, First=10, Second=5};

class Token {
    typeToken m_type;
    string m_symbol;
    double m_priority;
public:
    Token(typeToken type, string symbol) ;
    Token(typeToken type, char symbol) ;

    void addToSymbol(char symbol);
    typeToken getType();
    string getSymbol();
    double getPriority();
};

#endif //UNTITLED_TOKEN_H
