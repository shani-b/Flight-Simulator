//
// Created by shani on 15/12/2019.
//

#ifndef FLIGHT_SIMULATOR_COMMAND_H
#define FLIGHT_SIMULATOR_COMMAND_H

#include "Singelton.h"
#include <vector>

class Command {
public:
    virtual int execute(vector<string> tokens,int index) = 0;
};

class DefineVar: public Command {
public:
    int execute(vector<string> tokens,int index) {
        Singleton *s = s->getInstance();

        Variable *var = new Variable();
        var->setName(tokens[index+1]);

        //syntax: var name <-> sim
        if (tokens[index+1] == "->"){
            var->setSim(tokens[index +3]);
            s->getProg().insert(pair<string,Variable*>(tokens[index+1], var));
        } else if (tokens[index+1] == "<-"){
            var->setSim(tokens[index +3]);
            s->getSim().insert(pair<string,Variable*>(tokens[index+1], var));
        } else if (tokens[index+1] == "="){
            //TODO call set command
        }
    }
};


#endif //FLIGHT_SIMULATOR_COMMAND_H
