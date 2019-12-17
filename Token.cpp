//
// Created by shani on 08/11/2019.
//

#include "Token.h"
#include <string>


Token::Token(typeToken type, string symbol) {
        m_type = type;
        m_symbol += symbol;
        if (symbol == "+" || symbol == "-") {
            m_priority = 0;
        } else if (symbol == "*" || symbol == "/") {
            m_priority = 1;
        } else if (symbol == "%" || symbol == "$") {
            m_priority = 2;
        }
}

Token::Token(typeToken type, char symbol) {
    m_type = type;
    m_symbol += symbol;
    if (symbol == '+' || symbol == '-') {
        m_priority = 0;
    } else if (symbol == '*' || symbol == '/') {
        m_priority = 1;
    } else if (symbol == '%' || symbol == '$') {
        m_priority = 2;
    }

}

void Token::addToSymbol(char symbol) {
    m_symbol += symbol;
}

typeToken Token:: getType() {
    return m_type;
}
string Token::getSymbol() {
    return m_symbol;
}
double Token::getPriority() {
    return m_priority;
}