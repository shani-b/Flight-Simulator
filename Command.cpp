//
// Created by shani on 15/12/2019.
//

#include "Command.h"


int DefineVar::execute(vector<string> tokens, int index) {
    //define new var
    Variable *var = new Variable();
    var->setName(tokens[index+1]);

    //syntax: var name <-> sim njdcnsdkjn
    //add to the map of program
    if (tokens[index+2] == "->"){
        var->setSim(tokens[index +4]);
        s->addVarProg(var);
        //add to map of simulator
    } else
    if (tokens[index+2] == "<-"){
        var->setSim(tokens[index +4]);
        s->addVarSim(var);
    } else if (tokens[index+2] == "="){
        s->addVarProg(var);
        Command *c = new SetVar();
        c->execute(tokens, index + 1);
    }
    //TODO set new command for each var:
    //m_command[index+1] = new SetVar;

    return 4;
}

int SetVar::execute(vector<string> tokens, int index) {
    //syntax: name = expression

    //makeing an expression from the expression
    Interpreter *inter1 = new Interpreter();
    Expression *e = inter1->interpret(tokens[index + 2]);
    //set new value to the corresponding var

    if (s->getProg().find(tokens[index]) == s->getProg().end()){
        throw "No var in program";
    }
    auto var = s->getProg().find(tokens[index]);
    var->second->setValue(e->calculate());
    return 2;
}