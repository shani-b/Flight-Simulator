//
// Created by shani on 06/11/2019.
//
#include "Expression.h"
#include "Ex1.h"
#include <string>
#include <regex>

using namespace std;


Variable::Variable(string name, double value, string sim) {
    regex regex1("[a-zA-Z]+");
    regex regex2("[a-zA-Z]*_[0-9]*");
    regex regex3("[a-zA-Z]+[0-9]*");
    regex regex4("[a-zA-Z]_[a-zA-z]*");

    if (regex_match(name,regex1) || regex_match(name,regex2) || regex_match(name,regex3) || regex_match(name,regex4)) {
        m_name = name;
        m_value = value;
        m_sim = sim;
    }
    else {
        throw "bad input" ;
    }
}

Variable::Variable(string name, double value) {
    regex regex1("[a-zA-Z]+");
    regex regex2("[a-zA-Z]*_[0-9]*");
    regex regex3("[a-zA-Z]+[0-9]*");
    regex regex4("[a-zA-Z]_[a-zA-z]*");

    if (regex_match(name,regex1) || regex_match(name,regex2) || regex_match(name,regex3) || regex_match(name,regex4)) {
        m_name = name;
        m_value = value;
    }
    else {
        throw "bad input" ;
    }
}

void Variable::setName(string name) {
    m_name = name;
}
void Variable::setValue(double value) {
    m_value = value;
}
void Variable::setSim(string sim) {
    m_sim = sim;
}
Variable& Variable::operator ++() {
    ++m_value;
    return *this;
}

Variable& Variable::operator --() {
    --m_value;
    return *this;
}

Variable& Variable::operator +=(const double &num) {
    m_value = m_value + num;
    return *this;
}

Variable& Variable::operator -=(double const &num) {
    m_value = m_value - num;
    return *this;
}

Variable& Variable::operator ++(int) {
    Variable* tmp(this); // copy
    ++(*this);
    return *tmp;
}

Variable& Variable::operator --(int) {
    Variable* tmp(this); // copy
    --(*this);
    return *tmp;
}


double Variable::calculate() {
    return m_value;
}

double Variable::getValue() {
    return m_value;
}
string Variable::getVar() {
    return m_name;
}