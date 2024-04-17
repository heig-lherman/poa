/**
 * @file TIEInterceptor.cpp
 * @brief Implementation of the TIEInterceptor class
 */
#include "TIEInterceptor.hpp"

unsigned TIEInterceptor::idCounter = 0;

TIEInterceptor::TIEInterceptor() : TIEBase(++idCounter) {}

long double TIEInterceptor::getWeight() const {
    return 5;
}

unsigned long long TIEInterceptor::getMaximumSpeed() const {
    return 110;
}

std::string TIEInterceptor::getModelName() const {
    return TIEBase::getModelName() + "IN";
}