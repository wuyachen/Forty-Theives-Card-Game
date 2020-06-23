/**
 * \file CardADT.cpp
 * \author Emily Horsman <horsmane@mcmaster.ca>
 */
#include "CardADT.h"


CardT::CardT(SuitT S, RankT R) :
    m_s(S),
    m_r(R)
{}


SuitT CardT::suit() const {
    return m_s;
}


RankT CardT::rank() const {
    return m_r;
}


bool CardT::isRed() const {
    return m_s == Hearts || m_s == Diamonds;
}
