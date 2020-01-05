//
// Created by shani on 06/11/2019.
//
#include "Expression.h"
#include "Ex1.h"
#include <string>
#include <regex>
#include <utility>

using namespace std;


Variable::Variable(const string& name, double value, string sim) {
    regex regex1("[a-zA-Z]+");
    regex regex2("[a-zA-Z]*_[0-9]*");
    regex regex3("[a-zA-Z]+[0-9]*");
    regex regex4("[a-zA-Z]_[a-zA-z]*");

    if (regex_match(name,regex1) || regex_match(name,regex2) || regex_match(name,regex3) || regex_match(name,regex4)) {
        m_name = name;
        m_value = value;
        m_sim = std::move(sim);
        toSim = false;
    }
    else {
        throw "bad input" ;
    }
}

Variable::Variable(const string& name, double value) {
    regex regex1("[a-zA-Z]+");
    regex regex2("[a-zA-Z]*_[0-9]*");
    regex regex3("[a-zA-Z]+[0-9]*");
    regex regex4("[a-zA-Z]_[a-zA-z]*");

    if (regex_match(name,regex1) || regex_match(name,regex2) || regex_match(name,regex3) || regex_match(name,regex4)) {
        m_name = name;
        m_value = value;
        toSim = false;
    }
    else {
        throw "bad input" ;
    }
}

void Variable::setName(string name) {
    m_name = std::move(name);
}
void Variable::setValue(double value) {
    m_value = value;
}
void Variable::setSim(const string& sim) {
    m_sim = sim.substr(1, sim.size() - 2); // to delete the '/' in the beginning
}

void Variable::setToSim() {
    toSim = true;
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

Variable  Variable::operator ++(int) {
    Variable* tmp(this); // copy
    ++(*this);
    return *tmp;
}

Variable  Variable::operator --(int) {
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
string Variable::getName() {
    return m_name;
}
string Variable::getSim() {
    return m_sim;
}

bool Variable::isToSim() const {
    return toSim;
}