//
// Created by shani on 17/12/2019.
//

#include "Ex3.h"
#include "Command.h"

void Parser::parse(vector<string> tokens){

    for (int i = 0; i< tokens.size(); i++) {

        if (i == 25) {
            int c = 5;
        }


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
