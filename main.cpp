//
// Created by shani on 12/12/2019.
//

#include <string>
#include <vector>
#include "Singelton.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;
Singleton *Singleton::instance = NULL;
//vector<string> lexer(const char *fileName);

int main(int argc, char* argv[]) {
    Lexer lexer1;
    vector<string> tokens = lexer1.lexer("fly.txt");
    cout << "Lexing complete" <<endl;
    Parser parser1;
    try {
        parser1.parse(tokens);
    } catch (char const* e) {
        cout << e << endl;
    }
    string s;
    cin >> s;
    //TODO close all sockets via flags in singelon
    return 0;
}