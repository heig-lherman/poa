/**
 * @file TIEBase.cpp
 * @brief Implementation of the TIE abstract class
 */
#include "TIEBase.hpp"

TIEBase::TIEBase(unsigned int id) : Ship(id) {}

std::string TIEBase::getModelName() const {
    return "TIE/";
}
