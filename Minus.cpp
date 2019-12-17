//
// Created by shani on 06/11/2019.
//

#include "Ex1.h"

double Minus::calculate() {
    return m_left->calculate() - m_right->calculate();
}