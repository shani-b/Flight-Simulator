//
// Created by ofek on 18/12/2019.
//

#ifndef FLIGHT_SIMULATOR_PARSER_H
#define FLIGHT_SIMULATOR_PARSER_H
#include "Singelton.h"
#include "Command.h"
#include <string>
#include <unordered_map>
#include <vector>

class Parser {
    unordered_map <string,Command*> m_commands;
public:
    Parser() {
        m_commands["var"] = new DefineVar;
        m_commands["default"] = new SetVar;
        m_commands["openDataServer"] = new ServerCommand;
    }
    void parse(vector<string> tokens);
};
#endif //FLIGHT_SIMULATOR_PARSER_H
