/**
 * @file TIE.cpp
 * @brief Implementation of the TIE fighter class
 */
#include "TIE.hpp"

unsigned TIE::idCounter = 0;

long double TIE::getWeight() const {
    return 6;
}

unsigned long long TIE::getMaximumSpeed() const {
    return 100;
}

std::string TIE::getModelName() const {
    return TIEBase::getModelName() + "LN";
}

TIE::TIE() : TIEBase(++idCounter) {}
