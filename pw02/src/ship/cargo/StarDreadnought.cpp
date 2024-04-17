/**
 * @file StarDreadnought.cpp
 * @brief Implementation of the StarDreadnought class
 */
#include "StarDreadnought.hpp"

unsigned StarDreadnought::idCounter = 0;

StarDreadnought::StarDreadnought(double cargo)
    : CargoShip(cargo, ++idCounter, getMaximumCargoCapacity()) {}

long double StarDreadnought::getBaseWeight() const {
    return 9000000000;
}

long double StarDreadnought::getMaximumCargoCapacity() const {
    return 250000;
}

unsigned long long StarDreadnought::getMaximumSpeed() const {
    return 40;
}

std::string StarDreadnought::getModelName() const {
    return "Super-class Star Destroyer";
}
