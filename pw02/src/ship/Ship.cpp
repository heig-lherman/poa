/**
 * @file Ship.cpp
 * @brief Implementation of the Ship class
 */
#include "Ship.hpp"
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
