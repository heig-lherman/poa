/**
 * @file CargoShip.cpp
 * @brief Implementation of the CargoShip class
 */
#include "CargoShip.hpp"
#include <iomanip>

CargoShip::CargoShip(long double cargo,
                     unsigned id,
                     long double maxCargoCapacity)
    : Ship(id), cargo(validateCargo(cargo, maxCargoCapacity)) {}

long double CargoShip::getCargo() const {
    return this->cargo;
}

long double CargoShip::getWeight() const {
    return getBaseWeight() + getCargo();
}

std::ostream& CargoShip::formatToStream(std::ostream& os) const {
    Ship::formatToStream(os);
    os << "\n"
       << std::setprecision(1) << "cargo : " << getCargo()
       << " tons (max: " << getMaximumCargoCapacity() << ")";
    return os;
}

long double CargoShip::validateCargo(long double cargoAmount,
                                     long double maxCargoCapacity) {
    if (cargoAmount < 0) {
        throw std::invalid_argument("Cargo cannot be negative");
    }

    if (cargoAmount > maxCargoCapacity) {
        throw std::invalid_argument("Cargo exceeds maximum capacity");
    }

    return cargoAmount;
}
