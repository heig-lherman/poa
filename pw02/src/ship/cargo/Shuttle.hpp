#pragma once

#include "CargoShip.hpp"
/**
 * @file Shuttle.hpp
 * @brief Header file for the Shuttle class
 */
class Shuttle : public CargoShip {
public:
    /**
     * Constructor for the Shuttle class
     * @param cargo The ship's cargo in tons
     */
    explicit Shuttle(double cargo);

    /**
     * Retrieve the ship's weight in tons
     * @return The weight of the ship
     */
    [[nodiscard]] long double getBaseWeight() const override;

    /**
     * Retrieve the ship's maximum cargo capacity in tons
     * @return The maximum cargo capacity of the ship
     */
    [[nodiscard]] long double getMaximumCargoCapacity() const override;

    /**
     * Retrieve the ship's maximum speed in MGLT
     * @return The maximum speed of the ship
     */
    [[nodiscard]] unsigned long long getMaximumSpeed() const override;

    /**
     * Retrieve the ship's model
     * @return The name of the ship's model
     */
    [[nodiscard]] std::string getModelName() const override;

private:
    static unsigned idCounter;
};
