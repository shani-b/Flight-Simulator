//
// Created by shani on 17/12/2019.
//

#include "Ex3.h"
#include "Command.h"

void Parser::parse(vector<string> tokens){
    for (int i = 0; i< tokens.size(); i++) {
        Command *c = m_commands[tokens[i]];

        if (c != nullptr) {
            i += (c->execute(tokens, i));
        }

    }

}
