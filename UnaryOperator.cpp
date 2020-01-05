//
// Created by shani on 07/11/2019.
//

#include "Ex1.h"


UnaryOperator::UnaryOperator(Expression *exp) {
    m_exp = exp;
}

UnaryOperator::~UnaryOperator() {
    delete(m_exp);
}


