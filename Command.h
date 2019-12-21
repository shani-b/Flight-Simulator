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
    void readData(int socket);
    static void updateData(vector<double> vars);
public:
    int execute(vector<string> tokens,int index) override;
};

#endif //FLIGHT_SIMULATOR_COMMAND_H
