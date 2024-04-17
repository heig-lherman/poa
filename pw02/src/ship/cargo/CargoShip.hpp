#pragma once

#include "../Ship.hpp"
/**
 * @file CargoShip.hpp
 * @brief Declaration of the Cargo ship abstract class
 */
class CargoShip : public Ship {
protected:
    /**
     * Constructor for the CargoShip class
     * @throw std::invalid_argument if the cargo exceeds the maximum capacity
     * @param cargo The ship's cargo in tons
     * @param id The ship's unique identifier
     */
    CargoShip(long double cargo, unsigned id, long double maxCargoCapacity);

public:
    /**
     * Retrieve the ship's maximum cargo capacity in tons
     * @return The maximum cargo capacity of the ship
     */
    [[nodiscard]] virtual long double getMaximumCargoCapacity() const = 0;

    /**
     * Get the ship's current cargo in tons
     * @return The cargo of the ship
     */
    [[nodiscard]] virtual long double getCargo() const;

    /**
     * Retrieve the ship's total weight in tons
     * @return The total weight of the ship
     */
    [[nodiscard]] long double getWeight() const final;

    /**
     * Retrieve the ship's base weight in tons
     * @return The base weight of the ship
     */
    [[nodiscard]] virtual long double getBaseWeight() const = 0;

    /**
     * Format the ship's information and write it to the output stream
     * @param os The output stream to write to
     * @return The output stream
     */
    std::ostream& formatToStream(std::ostream& os) const override;

    /**
     * Validate that the cargo of the ship does not exceed the maximum capacity
     * @throw std::invalid_argument if the cargo exceeds the maximum capacity
     * @param cargoAmount The cargo to validate
     * @param maxCargoCapacity The maximum cargo capacity of the ship
     * @return The validated cargo
     */
    static long double validateCargo(long double cargoAmount,
                                     long double maxCargoCapacity);

private:
    long double cargo;  // in tons
};