//
// Created by shani on 12/12/2019.
//

#include <string>
#include <vector>
#include <unistd.h>
#include "Singelton.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;
Singleton *Singleton::instance = NULL;

int main(int argc, char* argv[]) {


    deque<int> ofek;

    Lexer lexer1;
    vector<string> tokens = lexer1.lexer("fly.txt");
    cout << "Lexing complete" <<endl;
    Parser parser1;

    Singleton *s = Singleton::getInstance(); // for debug

    try {
        parser1.parse(tokens);
    } catch (bad_alloc& e) {
        cout << e.what() << endl;
    }


//    string holder;
//    cin >> holder;// to hold the program active so it won't end

    s->serverShutdown();//telling the server to shut down
    while (!s->getServerIsDown()) {
        sleep(1);// wait until the server has closed the socket.
    }
    //TODO close all sockets via two-way flags in singelon
    // (one flag turn off here to signal the loop on each thread to stop iterating, one from the thread to signal that the socket closed.
    return 0;
}