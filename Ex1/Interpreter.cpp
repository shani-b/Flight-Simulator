//
// Created by shani on 08/11/2019.
//

#include "Ex1.h"
#include "../Token.h"
#include "../Singelton.h"
#include <deque>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;



bool isStrNum(string str);
deque<Token> strToArray(string str);
Expression* arrayToExpression(deque<Token> *tokens);

Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {
    m_listOfVar.clear();
}

bool Interpreter::isVarInList(string symbol) {
    Singleton *s = s->getInstance();

    if (s->getProg().count(symbol)){
        return true;
    }
    return false;
}

Expression* Interpreter::interpret(string str) {
    deque<Token> arrayOfTokens = strToArray(str);
    try {
        Expression* e =  arrayToExpression(&arrayOfTokens);
        return e;
    } catch (exception e) {
        throw "bad input";
    }
}

Expression* Interpreter::arrayToExpression(deque<Token> *tokens) {

    Singleton *s = s->getInstance();
    deque<Token> output;
    stack<Token> myStack;

    deque<Token>::iterator iter;

    //shunting yard algorithm
    for (iter = (*tokens).begin(); iter != (*tokens).end(); ++iter){
        if((*iter).getType() == Number) {
            output.push_back(*iter);
        } else if (((*iter).getType() == Operator ) || ((*iter).getType() == ConditionOperator)) {
            while (myStack.size() != 0 && myStack.top().getType() == Operator
                   && myStack.top().getType() != LeftBrace
                   &&((myStack.top().getPriority() > (*iter).getPriority())
                      || (myStack.top().getPriority() == (*iter).getPriority()))) {
                output.push_back(myStack.top());
                myStack.pop();
            }
            myStack.push(*iter);
        } else if ((*iter).getType() == LeftBrace) {
            myStack.push(*iter);
        } else if ((*iter).getType() == RightBrace) {
            while (myStack.size() != 0 && myStack.top().getType() != LeftBrace) {
                output.push_back(myStack.top());
                myStack.pop();
            }
            if (myStack.size() != 0 && myStack.top().getType() == LeftBrace) {
                myStack.pop();
            }
        }
    }


    while (myStack.size() != 0) {
        if ((myStack.top().getType() == Operator) || (myStack.top().getType() == ConditionOperator)) {
            output.push_back(myStack.top());
            myStack.pop();
        } else {
            throw "bad input";
        }
    }


    //converting postfix deque to expression
    Expression *a(nullptr);
    Expression *b(nullptr);
    stack<Expression*> mtFinalExp;
    bool flag = false;

    if (output.front().getType() == Number && (output.size()==1)) {
        flag = true;
    }

    while (output.size() != 0) {
        if (output.front().getType() == Number) {
            //check if its a variable in our list
            if (isVarInList(output.front().getSymbol())) {
                Variable *var;
                //check in which map it belong to
                //if (s->getSim().count(output.front().getSymbol())){
                //    var = s->getSim()[output.front().getSymbol()];
                //} else {
                var = s->getProg()[output.front().getSymbol()];
                //}
                //Variable *var = new Variable(m_listOfVar[output.front().getSymbol()]->getName()
                //        ,m_listOfVar[output.front().getSymbol()]->getValue());
                mtFinalExp.push(var);
                output.pop_front();
            }
            else { //its a number
                mtFinalExp.push(new Value(stod(output.front().getSymbol())));
                output.pop_front();
            };
        } else if ((output.front().getType() == Operator) || (output.front().getType() == ConditionOperator)) {
            flag = true;
            a = mtFinalExp.top();
            mtFinalExp.pop();
            if (output.front().getSymbol() == "%") {
                mtFinalExp.push(new UMinus(a));
            } else if (output.front().getSymbol() == "$") {
                mtFinalExp.push(new UPlus(a));
            } else {
                b = mtFinalExp.top();
                mtFinalExp.pop();

                if (output.front().getSymbol() == "+") {
                    mtFinalExp.push(new Plus(a,b));
                } else if (output.front().getSymbol() == "-") {
                    mtFinalExp.push(new Minus(b, a));
                } else if (output.front().getSymbol() == "*") {
                    mtFinalExp.push(new Mul(a,b));
                } else if (output.front().getSymbol() == "/") {
                    mtFinalExp.push(new Div(b,a));
                } else // all condition operator
                {
                    mtFinalExp.push(new BooleanExpression(b,a, output.front().getSymbol()));
                }
            }
            output.pop_front();
        }


    }/// end while



    if (flag) {
        return mtFinalExp.top();
    } else {
        throw "bad input";
    }

}

bool isStrNum(string str) {
    int numOfP = 0;
    int numOfM = 0;
    for (unsigned int i = 0; i < str.size(); i++) {
        if(!isdigit(str[i])){
            if (str[i] == '.' && (i+1) < str.size() && i !=0 ){
                numOfP++;
            } else if (str[i] == '-' && i == 0 &&  str.size() > 1) {
                numOfM++;
            } else {
                return false;
            }
        }
    }
    if (numOfP > 1) {
        return false;
    }
    if (numOfM >1) {
        return false;
    }
    return true;
}

deque<Token> strToArray(string s) {

    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == '-') {
            if (i == 0) {
                s.replace(0,1,"%");
            } else if (s[i-1] == '+' || s[i-1] == '-' || s[i-1] == '*' || s[i-1] == '/'
                ||s[i-1] == '('){
                    s.replace(i,1,"%");
            }
        } else if (s[i] == '+') {
            if (i == 0) {
                s.replace(0,1,"$");
            } else if (s[i-1] == '+' || s[i-1] == '-' || s[i-1] == '*' || s[i-1] == '/'
                       ||s[i-1] == '(' ){
                    s.replace(i,1,"$");
            }
        }
    }

    //divide the string to an array of tokens
    bool prevNum = false;
    deque<Token> arrayOfTokens;
    string mergeChar = "";

    for (unsigned int i = 0; i < s.size();i++){
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '$') {
            arrayOfTokens.push_back(*new Token(Operator, s[i]));
            prevNum = false;
        }else if (  s[i] == '('){
            arrayOfTokens.push_back(*new Token(LeftBrace, s[i]));
            prevNum = false;
        } else if (s[i] == ')') {
            arrayOfTokens.push_back(*new Token(RightBrace, s[i]));
            prevNum = false;
        } else if (s[i] == '<' || s[i] == '>' || s[i] == '=' ||  s[i] == '!'){
            //if <= or >= or == or != : 2 chars
            if (s[i+1] == '=') {
                 mergeChar  = s[i];
                 mergeChar += s[i+1];
                arrayOfTokens.push_back(*new Token(ConditionOperator, mergeChar));
                i++;
            } else {
                arrayOfTokens.push_back(*new Token(ConditionOperator, s[i]));
            }
            prevNum = false;
        }
        else if (s[i] == ' ') {
            //in case of space do nothing
            prevNum = false;
        } else {
            if (prevNum) {
                arrayOfTokens.back().addToSymbol(s[i]);
            } else {
                prevNum = true;
                arrayOfTokens.push_back(*new Token(Number, s[i]));
            }
        }
    }
    return arrayOfTokens;

}
