//
// Created by shani on 07/11/2019.
//

#ifndef UNTITLED_EX1_H
#define UNTITLED_EX1_H

#include "Expression.h"
#include "Token.h"
#include <map>
#include <unordered_map>
#include <deque>
#include <string>
#include <utility>


class UnaryOperator :public Expression{
protected:
    Expression* m_exp;
public:
    explicit UnaryOperator(Expression* exp);
    ~UnaryOperator() override;
    double calculate() override = 0;
};

class UPlus:public UnaryOperator{
public:
    explicit UPlus(Expression* exp):UnaryOperator(exp){}
    double calculate() override;
};

class UMinus:public UnaryOperator{
public:
    explicit UMinus(Expression* exp):UnaryOperator(exp){}
    double calculate() override;
};

class BinaryOperator :public Expression{
protected:
    Expression* m_right;
    Expression* m_left;
public:
    BinaryOperator(Expression* left, Expression* right);
    ~BinaryOperator() override;
    double calculate() override = 0;


};

class Plus :public BinaryOperator{
public:
    Plus(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate() override;
};

class Minus :public BinaryOperator{
public:
    Minus(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate() override;
};

class Mul :public BinaryOperator{
public:
    Mul(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate() override;
};

class Div :public BinaryOperator{
public:
    Div(Expression* left, Expression* right):BinaryOperator(left, right){}
    double calculate() override;
};

class Variable : public Expression{
    //members
    bool toSim{};
    string m_name;
    double m_value{};
    string m_sim;
public:
    Variable()= default;
    Variable(const string& name, double value, string sim);
    Variable(const string& name, double value);
    ~Variable() override = default;
    void setValue(double value);
    void setName(string name);
    void setSim(const string& sim);
    void setToSim();
    Variable& operator ++();
    Variable& operator --();
    Variable& operator +=(const double &num);
    Variable& operator -=(const double &num);
    Variable  operator++(int);
    Variable  operator--(int);
    double calculate() override;
    double getValue();
    string getName();
    string getSim();

    bool isToSim() const;
};

class Value: public Expression {
    double m_value;
public:
    explicit Value(double value);
    ~Value() override = default;
    double calculate() override;
};

class BooleanExpression: public BinaryOperator{
    string m_operator;
public:
    BooleanExpression(Expression* left, Expression* right, string operat):BinaryOperator(left, right), m_operator(move(operat)){}
    double calculate() override;
};

class Interpreter {
    unordered_map<string, Variable*> m_listOfVar;

public:
    Interpreter();
    virtual ~Interpreter();
    static Expression* interpret(string str);
    static bool isVarInList(const string& symbol);

    static Expression* arrayToExpression(deque<Token> *tokens);
};


#endif //UNTITLED_EX1_H
