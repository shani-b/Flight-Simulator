//
// Created by ofek on 18/12/2019.
//

#ifndef FLIGHT_SIMULATOR_PARSER_H
#define FLIGHT_SIMULATOR_PARSER_H
#include "Command.h"
#include <string>
#include <unordered_map>
#include <vector>

class Parser {
    static unordered_map <string,Command*> m_commands;
public:
    static void initParser() {
        m_commands["var"] = new DefineVar;
        m_commands["default"] = new SetVar;
        m_commands["while"] = new LoopCommand;
        m_commands["if"] = new IfCommand;
        m_commands["Print"] = new PrintCommand;
        m_commands["Sleep"] = new SleepCommand;
        m_commands["openDataServer"] = new ServerCommand;
        m_commands["connectControlClient"] = new ConnectControlClient;
        m_commands["func"] = new createFuncCommand;
    }

    static void addCommand(const string& commandName, Command *command);
    ~Parser();
    static void parse(vector<string> tokens);
};

#endif //FLIGHT_SIMULATOR_PARSER_H

