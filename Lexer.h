//
// Created by ofek on 18/12/2019.
//

#ifndef FLIGHT_SIMULATOR_LEXER_H
#define FLIGHT_SIMULATOR_LEXER_H

#include <string>
#include <vector>

using namespace std;

class Lexer {
public:
    Lexer() {}
    vector<string> lexer(const char *fileName);

};
#endif //FLIGHT_SIMULATOR_LEXER_H
