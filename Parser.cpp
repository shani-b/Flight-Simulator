//
// Created by shani on 17/12/2019.
//

#include "Command.h"
#include "Parser.h"
#include "Lexer.h"

void Parser::parse(vector<string> tokens){

    Singleton *s = s->getInstance();

    for (int i = 0; i< tokens.size(); i++) {
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
