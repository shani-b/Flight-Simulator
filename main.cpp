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
Singleton *Singleton::instance = nullptr;

int main(int argc, char* argv[]) {
    // FOR OFEK CHANGE IP IN FLY TO 10.0.2.2

    Lexer lexer1;
    vector<string> tokens = lexer1.lexer("fly.txt");
    cout << "Lexing complete" <<endl;
    Parser parser1;
    try {
        parser1.parse(tokens);
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    Singleton *s = Singleton::getInstance();
    s->programShutdown();//telling the server\client to shutdown
    while (!s->getCommunitactionsAreDown()) {
        sleep(1);// wait until the server and client has closed the socket.
    }
    return 0;
}