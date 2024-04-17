/**
 * @file Ship.cpp
 * @brief Implementation of the Ship class
 */
#include "Ship.hpp"
#include <cmath>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Ship& ship) {
    return ship.formatToStream(os);
}

void Ship::setNickname(const std::string& newNickname) {
    nickname = newNickname;
}

std::ostream& Ship::formatToStream(std::ostream& os) const {
    if (nickname.has_value()) {
        os << nickname.value() << " ";
    }
    os << "[" << getModelName() << " #" << id << "]\n";
    os << "weight : " << std::fixed << std::setprecision(2) << getWeight()
       << " tons\n";
    os << "max speed : " << getMaximumSpeed() << " MGLT";
    return os;
}

long double Ship::getConsumption(long double distance,
                                 long double speed) const {
    if (speed > getMaximumSpeed()) {
        throw std::invalid_argument(
            "Speed must be less than the ship's maximum speed");
    }

    return std::cbrt(getWeight()) / 2
           * log10l(getWeight() * speed)
           * log10l(distance + 1);
    ;
}
