//
// Created by shani on 19/12/2019.
//

#include "Ex1.h"

double BooleanExpression::calculate() {
    double left = m_left->calculate();
    double right = m_right->calculate();

    if (m_operator == "<"){
        return (left < right);
    } else if (m_operator == ">"){
        return (left > right);
    } else if (m_operator == "<="){
        return (left <= right);
    } else if (m_operator == ">="){
        return (left >= right);
    } else if (m_operator == "==") {
        return (left == right);
    } else if (m_operator == "!=") {
        return (left != right);
    } else {
        throw "operator condition not valid";
    }
}