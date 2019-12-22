//
// Created by shani on 15/12/2019.
//

#include "Command.h"
#include "Ex3.h"
#include <iostream>
#include <thread>

using namespace std::literals::chrono_literals;

int DefineVar::execute(vector<string> tokens, int index) {
    //define new var
    Variable *var = new Variable();
    var->setName(tokens[index+1]);

    //syntax: var name <-> sim njdcnsdkjn
    //add to the map of program
    if (tokens[index+2] == "->"){
        var->setName(tokens[index+1]);
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
        return 3;
    }

    return 4;
}

int SetVar::execute(vector<string> tokens, int index) {
    //syntax: name = expression

    //making an expression from the expression
    Interpreter *inter1 = new Interpreter();
    Expression *e = inter1->interpret(tokens[index + 2]);

    //set new value to the corresponding var
    if (s->getProg().find(tokens[index]) == s->getProg().end()){
        throw "No var in program";
    }
    auto var = s->getProg().find(tokens[index]);
    double x = e->calculate();
    var->second->setValue(e->calculate());
    return 2;

    //TODO send to simulator command
}

int IfCommand::execute(vector<string> tokens, int index) {

    //call parent execute function
    ConditionParser::execute(tokens,index);

    Parser parserForScope;

    if (m_condition->calculate()) {
        parserForScope.parse(m_scopeTokens);
    }

    return m_indexToJump;
}

int LoopCommand::execute(vector<string> tokens, int index) {

    //call parent execute function
    ConditionParser::execute(tokens,index);

    Parser parserForScope;

    while (m_condition->calculate()) {
        parserForScope.parse(m_scopeTokens);
    }

    return m_indexToJump;
}

int ConditionParser::execute(vector<string> tokens, int index) {
    //create boolean expression from condition:
    Interpreter interpretConditionl;
    m_condition = interpretConditionl.interpret(tokens[index +1]);


    //crate new array of tokens to the scope
    vector<string>::const_iterator first = tokens.begin() + index + 3;
    int i = 0;
    for (i = index + 3; i< tokens.size(); i++) {
        if (tokens[i] == "}")
            break;
    }
    vector<string>::const_iterator last = tokens.begin() + i;
    vector<string> scopeTockens(first, last);
    m_scopeTokens = scopeTockens;
    m_indexToJump = i - index;

}

int PrintCommand::execute(vector<string> tokens, int index) {
    cout<< tokens[index+1];
    return 1;
}

int SleepCommand::execute(vector<string> tokens, int index) {
    int time = stod(tokens[index +1]);
    std::this_thread::sleep_for(chrono::milliseconds(time));
    return 1;
}