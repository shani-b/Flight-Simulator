//
// Created by shani on 17/12/2019.
//

#include "Parser.h"
#include "Lexer.h"

unordered_map<string,Command*> Parser::m_commands;

void Parser::parse(vector<string> tokens){

    for (int i = 0; i< tokens.size(); i++) {
        auto token = tokens[i];
        auto it = m_commands.find(tokens[i]);
        if (it == m_commands.end()){
            if (tokens[i +1] == "var") {
                it = m_commands.find("func");
            } else { //creating new var
                it = m_commands.find("default");
            }
        }
        Command *c = it->second;

        if (c != nullptr) {
            i += (c->execute(tokens, i));
        }
    }
}

Parser::~Parser() {
    delete(m_commands["var"]);
    delete(m_commands["default"]);
    delete(m_commands["while"]);
    delete(m_commands["if"]);
    delete(m_commands["Print"]);
    delete(m_commands["Sleep"]);
    delete(m_commands["openDataServer"]);
    delete(m_commands["connectControlClient"]);
    //TODO fix destructor
}

void Parser::addCommand(const string& commandName, Command *command) {
    m_commands[commandName] = command;
}
