//
// Created by shani on 06/11/2019.
//

#include "Ex1.h"

double Div::calculate() {
       if (m_right->calculate() == 0){
           throw "bad input";
       }
    return m_left->calculate() / m_right->calculate();
}