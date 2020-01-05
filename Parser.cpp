//
// Created by shani on 17/12/2019.
//

#include "Command.h"
#include "Parser.h"
#include "Lexer.h"

/**
 * Creating and executing the commands received in the list from the Lexer.
 * @param tokens
 */
void Parser::parse(vector<string> tokens){

    for (unsigned i = 0; i< tokens.size(); i++) {

        auto token = tokens[i];
        auto it = m_commands.find(tokens[i]);
        if (it == m_commands.end()){
            it = m_commands.find("default");
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
}
