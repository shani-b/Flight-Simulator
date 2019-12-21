//
// Created by shani on 15/12/2019.
//

#ifndef FLIGHT_SIMULATOR_SINGELTON_H
#define FLIGHT_SIMULATOR_SINGELTON_H

#include "Ex1/Ex1.h"
#include <unordered_map>
#include <thread>

class Singleton {
    static Singleton *instance;
    unordered_map<string,Variable*> progVars;
    unordered_map<string,Variable*> simVars;
    bool server_flag = true;

    // Private constructor so that no objects can be created.
    Singleton() = default;

public:
    static Singleton *getInstance() {
        if (!instance)
            instance = new Singleton;
        return instance;
    }

    unordered_map<string ,Variable*> getProg() {
        return this -> progVars;
    }

    unordered_map<string ,Variable*> getSim() {
        return this -> simVars;
    }

    void addVarProg(Variable *var) {
        this -> progVars[var->getName()] = var;
    }

    void addVarSim(Variable *var) {
        this -> simVars[var->getSim()] = var;
    }

    bool serverStatus() {
        return server_flag;
    }

    void serverShutdown() {
        this -> server_flag = false;
    }
};

#endif //FLIGHT_SIMULATOR_SINGELTON_H
