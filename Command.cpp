//
// Created by shani on 15/12/2019.
//

class Command {
public:
    virtual int execute() = 0;
    virtual ~Command() = 0;

};

class DefineVar: Command {
public:
    int execute() {

    }
};