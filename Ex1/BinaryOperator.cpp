//
// Created by shani on 06/11/2019.
//

#include "Ex1.h"

BinaryOperator:: BinaryOperator(Expression* left, Expression* right) {
    m_left = left;
    m_right = right;
}

BinaryOperator::~BinaryOperator() {
    delete(m_right);
    delete(m_left);
}