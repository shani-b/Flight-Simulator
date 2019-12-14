//
// Created by shani on 12/12/2019.
//

#include <string>
#include <list>
#include <fstream>
#include <iostream>

using namespace std;

list<string> lexer(const char *fileName);

int main(int argc, char* argv[]) {
    printf("hello\n");

    //lexer(argv[1]);
    lexer("fly.txt");
    return 0;
}

list<string> lexer(const char *fileName) {

    fstream file{fileName, ios::in};
    list<string> tokens;
    string line, str;
    bool inStr = false;


    if (!file) {
        printf("Error! opening file");
        exit(1);
    }


    while (getline(file, line)) {

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '\"'){
                inStr = !inStr;
            }
            if (line[i] == '\t') {
                i++;
            }
            if ((line[i] == '(') || (line[i] == ')') || (line[i] == ',')) {
                tokens.push_back(str);
                str = "";
            } else if (line[i] == ' ') {
                if (inStr){
                    str += line[i];
                } else {
                    tokens.push_back(str);
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
        }
    }
    cout<<"done";
    return tokens;

}