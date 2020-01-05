//
// Created by shani on 15/12/2019.
//

#ifndef FLIGHT_SIMULATOR_SINGELTON_H
#define FLIGHT_SIMULATOR_SINGELTON_H

#include "Ex1.h"
#include <unordered_map>
#include <thread>

/**
 * A class with one instance.
 */
class Singleton {
    static Singleton *instance;
    unordered_map<string,Variable*> progVars;
    unordered_map<string,Variable*> simVars;
    deque<string> m_commandsToSend;
    bool communication_flag = true;
    bool servernIsDown = false;
    bool clientIsDown = false;

    // Private constructor so that no objects can be created.
    Singleton() = default;

public:
    //create only one instance of class
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

    deque<string> getCommandsToSend() {
        return m_commandsToSend;
    }

    void removeFrontCommand(){
        m_commandsToSend.pop_front();
    }

    void addNewCommandToSend(const string& str) {
        m_commandsToSend.push_back(str);
    }

    void addVarProg(Variable *var) {
        this -> progVars[var->getName()] = var;
    }

    void addVarSim(Variable *var) {
        this -> simVars[var->getSim()] = var;
    }

    bool getCommunicationStatus() {
        return communication_flag;
    }

    bool getCommunitactionsAreDown() {
        return servernIsDown && clientIsDown;
    }

    void serverClosed() {
        this->servernIsDown = true;
    }

    void clientClosed() {
        this->clientIsDown = true;
    }

    void programShutdown() {
        this -> communication_flag = false;
    }
};

#endif //FLIGHT_SIMULATOR_SINGELTON_H
