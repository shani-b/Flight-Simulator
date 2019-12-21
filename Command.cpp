//
// Created by shani on 15/12/2019.
//

#include <netinet/in.h>
#include <unistd.h>
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
    Singleton *s = s->getInstance();
    int i = 0;
    char buffer[10240] = {0};
    while (s->serverStatus()) {
        i++;
        cout << i << endl;
        read(socket , buffer, 1024);
        cout<<buffer<<endl<<endl;
        sleep(1);
    }
}