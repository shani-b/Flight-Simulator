//
// Created by shani on 15/12/2019.
//

#include <netinet/in.h>
#include <unistd.h>
#include "Command.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include "Parser.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <mutex>


mutex mutex_lock;

using namespace std;

int DefineVar::execute(vector<string> tokens, int index) {

    //define new var
    auto *var = new Variable();
    var->setName(tokens[index+1]);

    //syntax: var name <-> sim "path"
    if (tokens[index+2] == "->") {
        var->setToSim();
        var->setSim(tokens[index +4]);
        s->addVarProg(var);
    } else if (tokens[index+2] == "<-") {
        var->setSim(tokens[index +4]);
        s->addVarProg(var);
        s->addVarSim(var);
    } else if (tokens[index+2] == "=") {
        s->addVarProg(var);
        Command *c = new SetVar();
        c->execute(tokens, index + 1);
        return 3;
    }
    return 4;
}

int SetVar::execute(vector<string> tokens, int index) {
    //syntax: name = expression

    string setToSim;

    //making an expression from the expression
    auto *inter1 = new Interpreter();
    Expression *e = inter1->interpret(tokens[index + 2]);

    //set new value to the corresponding var
    if (s->getProg().find(tokens[index]) == s->getProg().end()){
        throw "No var in program";
    }
    auto var = s->getProg().find(tokens[index]);
    var->second->setValue(e->calculate());

    mutex_lock.lock();
    //add string to list of commands to sent to simulator
    if (var->second->isToSim()) {
        setToSim = "set " + var->second->getSim() + " " + to_string(var->second->getValue()) + "\r\n";
        s->addNewCommandToSend(setToSim);
    }
    mutex_lock.unlock();

    return 2;
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
    if (tokens[index +1][0] == '"') {
        cout<< tokens[index+1]<<endl;
    } else  {
        cout<< (s->getProg()[tokens[index + 1]])->getValue() <<endl;
    }
    return 1;
}

int SleepCommand::execute(vector<string> tokens, int index) {
    int time = stoi(tokens[index +1]);
    this_thread::sleep_for(chrono::milliseconds(time));
    return 1;
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
    while (s->getServerStatus()) {
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
    close(socket);
    s->socketClosed(); //telling main that the server is ready to be close
}

void ServerCommand::updateData(vector<double> vars) {
    int i;
    Singleton *s = Singleton::getInstance();
    unordered_map<string, Variable*> map = s->getSim();
    auto iter = map.end();
    for (i = 0; i < vars.size(); i++) {
        switch (i) {
            case 0:
                iter = map.find("/instrumentation/airspeed-indicator/indicated-speed-kt");
                break;
            case 1:
                iter = map.find("/sim/time/warp");
                break;
            case 2:
                iter = map.find("/controls/switches/magnetos");
                break;
            case 3:
                iter = map.find("/instrumentation/heading-indicator/offset-deg");
                break;
            case 4:
                iter = map.find("/instrumentation/altimeter/indicated-altitude-ft");
                break;
            case 5:
                iter = map.find("/instrumentation/altimeter/pressure-alt-ft");
                break;
            case 6:
                iter = map.find("/instrumentation/attitude-indicator/indicated-pitch-deg");
                break;
            case 7:
                iter = map.find("/instrumentation/attitude-indicator/indicated-roll-deg");
                break;
            case 8:
                iter = map.find("/instrumentation/attitude-indicator/internal-pitch-deg");
                break;
            case 9:
                iter = map.find("/instrumentation/attitude-indicator/internal-roll-deg");
                break;
            case 10:
                iter = map.find("/instrumentation/encoder/indicated-altitude-ft");
                break;
            case 11:
                iter = map.find("/instrumentation/encoder/pressure-alt-ft");
                break;
            case 12:
                iter = map.find("/instrumentation/gps/indicated-altitude-ft");
                break;
            case 13:
                iter = map.find("/instrumentation/gps/indicated-ground-speed-kt");
                break;
            case 14:
                iter = map.find("/instrumentation/gps/indicated-vertical-speed");
                break;
            case 15:
                iter = map.find("/instrumentation/heading-indicator/indicated-heading-deg");
                break;
            case 16:
                iter = map.find("/instrumentation/magnetic-compass/indicated-heading-deg");
                break;
            case 17:
                iter = map.find("/instrumentation/slip-skid-ball/indicated-slip-skid");
                break;
            case 18:
                iter = map.find("/instrumentation/turn-indicator/indicated-turn-rate");
                break;
            case 19:
                iter = map.find("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
                break;
            case 20:
                iter = map.find("/controls/flight/aileron");
                break;
            case 21:
                iter = map.find("/controls/flight/elevator");
                break;
            case 22:
                iter = map.find("/controls/flight/rudder");
                break;
            case 23:
                iter = map.find("/controls/flight/flaps");
                break;
            case 24:
                iter = map.find("/controls/engines/engine/throttle");
                break;
            case 25:
                iter = map.find("/controls/engines/current-engine/throttle");
                break;
            case 26:
                iter = map.find("/controls/switches/master-avionics");
                break;
            case 27:
                iter = map.find("/controls/switches/starter");
                break;
            case 28:
                iter = map.find("/engines/active-engine/auto-start");
                break;
            case 29:
                iter = map.find("/controls/flight/speedbrake");
                break;
            case 30:
                iter = map.find("/sim/model/c172p/brake-parking");
                break;
            case 31:
                iter = map.find("/controls/engines/engine/primer");
                break;
            case 32:
                iter = map.find("/controls/engines/current-engine/mixture");
                break;
            case 33:
                iter = map.find("/controls/switches/master-bat");
                break;
            case 34:
                iter = map.find("/controls/switches/master-alt");
                break;
            case 35:
                iter = map.find("/engines/engine/rpm");
                break;
            default:
                cout << "didnt find var in simVar - updateData  i = " << i << endl;
                continue;
        }
        if (iter == map.end()) {
            continue;
        } else {
            if (!iter->second->isToSim()) {
                double temp = iter->second->getValue();
                iter->second->setValue(vars[i]);

            }
        }
        cout<<"im out of loop1"<<endl;
    }
}

int ConnectControlClient::execute(vector<string> tokens, int index) {

    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(stoi(tokens[index +2]));
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }


    //TODO close socket?
    thread t1([this, client_socket] { this->sendCommands(client_socket); });
    t1.detach();
    return 2;
}

void ConnectControlClient::sendCommands(int client_socket) {


    Singleton *s = s->getInstance();
    const char* commandToSend;
    string message;

    while (s->getServerStatus()) {

        try {
            mutex_lock.lock();
            if (!s->getCommandsToSend().empty()) {

                message = (s->getCommandsToSend().front());
                commandToSend = message.c_str();
                s->removeFrontCommand();

                ssize_t is_sent = write(client_socket, commandToSend, message.length());
                if (is_sent == -1) {
                    std::cout << "Error sending message" << std::endl;
                } else {
                    // std::cout<< commandToSend <<std::endl;
                }

            }
            mutex_lock.unlock();
        } catch (exception e ) {
            cout << e.what() <<endl;
        }

    }
    cout<<"in out of loop2"<<endl;



}

