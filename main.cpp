//
// Created by shani on 12/12/2019.
//

#include <string>
#include <iostream>
#include <vector>
#include "Singelton.h"
#include "Ex3.h"

using namespace std;
Singleton *Singleton::instance = NULL;

vector<string> lexer(const char *fileName);

int main(int argc, char* argv[]) {
    printf("hello\n");

    Lexer lexer1;
    vector<string> tokens = lexer1.lexer("fly.txt");
    Parser parser1;
    parser1.parse(tokens);

    Singleton *s = s->getInstance();


    return 0;
}