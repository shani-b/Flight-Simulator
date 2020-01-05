//
// Created by shani on 17/12/2019.
//

#include "Lexer.h"
#include <fstream>


/**
 * the lexer read file and create a list (vector) of tokens which represent commands for fly simulator
 * @param fileName
 * @return list of string
 */
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

    //read lines from file
    while (getline(file, line)) {
        //read chars in line
        for (unsigned i = 0; i < line.length(); i++) {

            if ((str == "while") || (str == "if")) {
                tokens.push_back(str);
                str = "";
                inStr = true;
            }
            if (line[i] == '=' && !inStr) {
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
            } else if ((line[i] == '{') || (line[i] == '}')) {
                if (!str.empty()){
                    tokens.push_back(str);
                }
                str = line[i];
                tokens.push_back(str);
                str = "";
                inStr = false;
            } else {
                str += line[i];
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
