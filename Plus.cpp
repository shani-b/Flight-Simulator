//
// Created by shani on 06/11/2019.
//

#include "Ex1.h"

double Plus::calculate() {
    return m_right->calculate() + m_left->calculate();
}
