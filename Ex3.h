//
// Created by shani on 17/12/2019.
//

#ifndef FLIGHT_SIMULATOR_EX3_H
#define FLIGHT_SIMULATOR_EX3_H

#include "Singelton.h"
#include "Command.h"
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Lexer {
public:
    Lexer() {}
    vector<string> lexer(const char *fileName);

};


class Parser {
    unordered_map <string,Command*> m_commands;
public:
    Parser() {
        m_commands["var"] = new DefineVar;
        m_commands["default"] = new SetVar;
    }
    void parse(vector<string> tokens);
};


#endif //FLIGHT_SIMULATOR_EX3_H
