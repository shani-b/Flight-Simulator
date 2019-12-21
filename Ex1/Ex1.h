//
// Created by shani on 07/11/2019.
//

#ifndef UNTITLED_EX1_H
#define UNTITLED_EX1_H

#include "Expression.h"
#include "../Token.h"
#include <map>
#include <unordered_map>
#include <deque>
#include <string>


class UnaryOperator :public Expression{
protected:
    Expression* m_exp;
public:
    UnaryOperator(Expression* exp);
    virtual ~UnaryOperator();
    virtual double calculate()= 0;
};

class UPlus:public UnaryOperator{
public:
    UPlus(Expression* exp):UnaryOperator(exp){}
    double calculate();
};

class UMinus:public UnaryOperator{
public:
    UMinus(Expression* exp):UnaryOperator(exp){}
    double calculate();
};

class BinaryOperator :public Expression{
protected:
    Expression* m_right;
    Expression* m_left;
public:
    BinaryOperator(Expression* left, Expression* right);
    virtual ~BinaryOperator();
    virtual double calculate() = 0;


};

class Plus :public BinaryOperator{
public:
    Plus(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
};

class Minus :public BinaryOperator{
public:
    Minus(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
};

class Mul :public BinaryOperator{
public:
    Mul(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
};

class Div :public BinaryOperator{
public:
    Div(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate();
};

class Variable : public Expression{
    //members
    bool toSim;
    string m_name;
    double m_value;
    string m_sim;
public:
    Variable(){}
    Variable(string name, double value, string sim);
    Variable(string name, double value);
    ~Variable(){};
    void setValue(double value);
    void setName(string name);
    void setSim(string sim);
    void setToSim();
    Variable& operator ++();
    Variable& operator --();
    Variable& operator +=(const double &num);
    Variable& operator -=(const double &num);
    Variable& operator++(int);
    Variable& operator--(int);
    double calculate();
    double getValue();
    string getName();
    string getSim();

    bool isToSim() const;
};

class Value: public Expression {
    double m_value;
public:
    Value(double value);
    ~Value(){};
    double calculate();
};

class Interpreter {
    //map<string, Variable*> m_listOfVar;
    unordered_map<string, Variable*> m_listOfVar;
public:
    Interpreter();
    virtual ~Interpreter();
    Expression* interpret(string str);
    bool isVarInList(string symbol);

    Expression* arrayToExpression(deque<Token> *tokens);
};


#endif //UNTITLED_EX1_H
