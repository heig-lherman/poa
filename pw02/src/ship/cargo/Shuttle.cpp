/**
 * @file Shuttle.cpp
 * @brief Implementaiton of the Shuttle class
 */
#include "Shuttle.hpp"

unsigned Shuttle::idCounter = 0;

Shuttle::Shuttle(double cargo)
    : CargoShip(cargo, ++idCounter, getMaximumCargoCapacity()) {}

long double Shuttle::getBaseWeight() const {
    return 360;
}

long double Shuttle::getMaximumCargoCapacity() const {
    return 80;
}

unsigned long long Shuttle::getMaximumSpeed() const {
    return 54;
}

std::string Shuttle::getModelName() const {
    return "Lambda-class Shuttle";
}
