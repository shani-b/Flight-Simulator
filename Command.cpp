//
// Created by shani on 15/12/2019.
//

#include <netinet/in.h>
#include <unistd.h>
#include "Command.h"
#include <vector>
#include <algorithm>

int DefineVar::execute(vector<string> tokens, int index) {
    //define new var
    auto *var = new Variable();
    var->setName(tokens[index+1]);

    //syntax: var name <-> sim "path"
    //add to the map of program
    if (tokens[index+2] == "->"){
        var->setToSim();
        var->setSim(tokens[index +4]);
        s->addVarProg(var);
    } else
    if (tokens[index+2] == "<-"){
        var->setSim(tokens[index +4]);
        s->addVarProg(var);
    } else if (tokens[index+2] == "="){
        s->addVarProg(var);
        auto existingVar = s->getProg().find(tokens[index+3]);
        if (existingVar == s->getProg().end()) {
            throw "No var in program";
        }
        var->setValue(existingVar->second->getValue());
        s->addVarProg(var);
        /*
        Command *c = new SetVar();
        c->execute(tokens, index + 1);
         *///TODO do we need that anymore?
    }

    //TODO set new command for each var: same ^^
    //m_command[index+1] = new SetVar;
    return 4;
}

int SetVar::execute(vector<string> tokens, int index) {
    //syntax: name = expression

    //making an expression from the expression
    auto *inter1 = new Interpreter();
    Expression *e = inter1->interpret(tokens[index + 2]);
    //set new value to the corresponding var

    if (s->getProg().find(tokens[index]) == s->getProg().end()){
        throw "No var in program";
    }
    auto var = s->getProg().find(tokens[index]);
    var->second->setValue(e->calculate());
    //TODO check var->toSim : if TRUE - send data to simulator.
    return 2;
}

int ServerCommand::execute(vector<string> tokens, int index) {
    index++;
    int port = stoi(tokens[index]);

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //bind socket to IP address
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Server - Could not bind the socket to an IP"<<std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Server - Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t*)&address);
    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }
    cout << "connection successful" << endl;
    close(socketfd); //closing the listening socket
    //s->createServer(client_socket, this)
    thread t1([this, client_socket] { this->readData(client_socket); });
    t1.detach();
    cout <<"scope ended"<<endl;
    return index;
}

void ServerCommand::readData(int socket) {
    cout <<"thread entered"<<endl;
    int i;
    double value;
    Singleton *s = Singleton::getInstance();
    char buffer[1] = {0};
    char curVar[100] = {0};
    vector<double> variables;

    while (s->serverStatus()) {
        read(socket, buffer, 1);
        for (i = 0; buffer[0] != ','; i++) {
            if (buffer[0] == '\n') {
                break;
            }
            curVar[i] = buffer[0];
            read(socket, buffer, 1);
        }
        value = stod(curVar);
        variables.push_back(value);
        fill(curVar, curVar + i, 0);
        if (buffer[0] == '\n') {
            updateData(variables);
            variables.clear();
        }
    }
}

void ServerCommand::updateData(vector<double> vars) {
    int i;
    for (i = 0; i < vars.size(); i++) {
        switch (i) {
            case 1:
        }
    }
}
