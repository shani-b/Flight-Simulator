//
// Created by shani on 17/12/2019.
//

#include "Lexer.h"
#include <fstream>

vector <string> Lexer::lexer(const char *fileName) {

    fstream file{fileName, ios::in};
    vector<string> tokens;
    string line, str;
    bool inStr = false;
    bool inExpression = false;

    if (!file) {
        printf("Error! opening file");
        exit(1);
    }


    while (getline(file, line)) {

        for (int i = 0; i < line.length(); i++) {

            if (line[i] == '=') {
                if (!str.empty()){
                    tokens.push_back(str);
                }
                tokens.push_back("=");
                str = "";
                inExpression = true;
                i++;

            }
            if (line[i] == '\"'){
                inStr = !inStr;
            }
            if (line[i] == '\t') {
                i++;
            }
            if (!inExpression && ((line[i] == '(') || (line[i] == ')') || (line[i] == ','))) {
                tokens.push_back(str);
                str = "";
            } else if (!inExpression && (line[i] == ' ')) {
                if (inStr){
                    str += line[i];
                } else {
                    if (!str.empty()) {
                        tokens.push_back(str);
                    }
                    str = "";
                }
            }else {
                str += line[i];
            }
            if (line[i] == '{' | line[i] == '}') {
                tokens.push_back(str);
                str = "";
            }
        }
        if (!str.empty()){
            tokens.push_back(str);
            str ="";
            inExpression = false;
        }
    }
    return tokens;

}
