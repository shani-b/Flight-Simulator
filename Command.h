//
// Created by shani on 15/12/2019.
//

#ifndef FLIGHT_SIMULATOR_COMMAND_H
#define FLIGHT_SIMULATOR_COMMAND_H

#include "Singelton.h"
#include <vector>
#include <iostream>

class Command {
protected:
    Singleton *s = Singleton::getInstance();
public:
    virtual int execute(vector<string> tokens,int index) = 0;
    virtual ~Command() = default;
};

class DefineVar: public Command {
public:
    int execute(vector<string> tokens,int index) override;
};

class SetVar: public Command {
public:
    int execute(vector<string> tokens,int index) override;
};

class ServerCommand: public Command {
    static void readData(int socket);
    static void updateData(vector<double> vars);
public:
    int execute(vector<string> tokens,int index) override;
};

class ConnectControlClient: public Command{
    static void sendCommands(int socket);
public:
    int execute(vector<string> tokens,int index) override;
};


class ConditionParser: public Command{
protected:
    Expression *m_condition;
    vector<string> m_scopeTokens;
    int m_indexToJump;
public:
    int execute(vector<string> tokens,int index) override;
};

class LoopCommand: public ConditionParser{
public:
    int execute(vector<string> tokens,int index) override;

};

class IfCommand: public ConditionParser{
public:
    int execute(vector<string> tokens,int index) override;
};

class PrintCommand: public Command{
public:
    int execute(vector<string> tokens,int index) override;
};

class SleepCommand: public Command{
public:
    int execute(vector<string> tokens, int index) override;
};

class createFuncCommand: public Command{
public:
    int execute(vector<string> tokens,int index) override;
};

class funcCommand: public Command {
    vector<string> m_scope;
public:
    explicit funcCommand(const vector<string>& scope);

    int execute(vector<string> tokens,int index) override;
};
#endif //FLIGHT_SIMULATOR_COMMAND_H
