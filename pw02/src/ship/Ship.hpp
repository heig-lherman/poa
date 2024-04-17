#pragma once

#include <optional>
#include <ostream>
/**
 * @file Ship.hpp
 * @brief File containing the definition of the Ship class
 */
class Ship;

/**
 * Overload the << operator to allow for easy printing of a Ship object
 * @param os The output stream to write to
 * @param ship The ship to write to the output stream
 * @return The output stream
 */
std::ostream& operator<<(std::ostream& os, const Ship& ship);

class Ship {
protected:
    /**
     * Construct a new Ship object with the given id
     * @param id the id of the ship
     */
    explicit Ship(unsigned id) : id(id){};

public:
    /**
     * Virtual destructor for the Ship class (in case one of the subclass would
     * want to degine and override it).
     */
    virtual ~Ship() = default;

    /**
     * Retrieve the ship's model
     * @return The name of the ship's model
     */
    [[nodiscard]] virtual std::string getModelName() const = 0;

    /**
     * Retrieve the ship's weight in tons
     * @return The weight of the ship
     */
    [[nodiscard]] virtual long double getWeight() const = 0;

    /**
     * Retrieve the ship's maximum speed in MGLT
     * @return The maximum speed of the ship
     */
    [[nodiscard]] virtual unsigned long long getMaximumSpeed() const = 0;

    /**
     * Set a newNickname for the ship
     * @param newNickname the new newNickname chosen
     */
    void setNickname(const std::string& newNickname);

    /**
     * Format the ship's information and write it to the output stream
     * @param os The output stream to write to
     * @return The output stream
     */
    virtual std::ostream& formatToStream(std::ostream& os) const;

    /**
     * Retrieve the consumption of the ship
     * @param distance the distance to travel
     * @param speed the speed at which to travel
     * @return the consumption of the ship
     * @throw invalid_argument if the distance is negative
     * @throw invalid_argument if the speed is negative or greater than
     *                         the squadron's maximum speed
     */
    [[nodiscard]] long double getConsumption(long double distance,
                                             long double speed) const;

private:
    std::optional<std::string> nickname;
    unsigned id;
};
