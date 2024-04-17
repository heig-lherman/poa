#pragma once

#include "ship/Ship.hpp"
/**
 * @file Squadron.hpp
 * @brief Definition of the Squadron class
 */
class Squadron;

/**
 * Output stream operator for the Squadron class
 * @param os the output stream
 * @param squadron the squadron to output
 * @return the output stream
 */
std::ostream &operator<<(std::ostream &os, const Squadron &squadron);

/**
 * Operator + to add a ship to a squadron
 * @param squadron the squadron to add to
 * @param ship the ship to add
 * @return the squadron with the ship added
 */
Squadron operator+(const Squadron &squadron, Ship &ship);

/**
 * Operator - to remove a ship from a squadron
 * @param squadron the squadron to remove from
 * @param ship the ship to remove
 * @return the squadron with the ship removed
 */
Squadron operator-(const Squadron &squadron, const Ship &ship);

class Squadron {
    struct Node;

public:

    /**
     * Construct a new Squadron object with the given name
     * @param name the name of the squadron
     */
    explicit Squadron(const std::string &name);

    /**
     * Copy constructor for the Squadron class
     * @param other the squadron to copy
     */
    Squadron(const Squadron &other);

    /**
     * Move constructor for the Squadron class
     * @param other the squadron to move
     */
    Squadron(Squadron &&other) noexcept;

    /**
     * Destructor for the Squadron class
     */
    ~Squadron() noexcept;

    /**
     * Copy assignment operator for the Squadron class
     * @param other the squadron to copy
     * @return a reference to the squadron that was copied
     */
    Squadron &operator=(const Squadron &other);

    /**
     * Move assignment operator for the Squadron class
     * @param other the squadron to move
     * @return a reference to the squadron that was moved
     */
    Squadron &operator=(Squadron &&other) noexcept;

    /**
     * Operator += to add a ship to a squadron
     * @param ship the ship to add
     * @return a reference to the squadron with the ship added
     */
    Squadron &operator+=(Ship &ship);

    /**
     * Operator -= to remove a ship from a squadron
     * @param ship the ship to remove
     * @return a reference to the squadron with the ship removed
     */
    Squadron &operator-=(const Ship &ship);

    /**
     * Add a ship to the squadron
     * @param ship the ship to add
     * @return a new squadron with the ship added
     */
    [[nodiscard]] Squadron addShipCopy(Ship &ship) const;

    /**
     * Add a ship to the squadron
     * @param ship the ship to add
     * @return a reference to the squadron with the ship added
     */
    Squadron &addShip(Ship &ship);

    /**
     * Remove a ship from the squadron
     * @param ship the ship to remove
     * @return a new squadron with the ship removed
     */
    [[nodiscard]] Squadron removeShipCopy(const Ship &ship) const;

    /**
     * Remove a ship from the squadron
     * @param ship the ship to remove
     * @return a reference to the squadron with the ship removed
     */
    Squadron &removeShip(const Ship &ship);

    /**
     * Set the newName of the squadron
     * @param newName the newName to set
     */
    void setName(const std::string &newName);

    /**
     * Set the leader of the squadron
     * @param ship the ship to set as the leader
     */
    void setLeader(Ship &ship);

    /**
     * Remove the leader of the squadron
     */
    void removeLeader();

    /**
     * Retrieve the ship at the given index of the squadron
     * @param index the index of the ship to retrieve
     * @return the ship at the given index of the squadron
     * @throw out_of_range if the index is out of bounds
     */
    [[nodiscard]] Ship &get(size_t index) const;

    /**
     * Retrieve the consumption of the squadron
     * @param distance the distance to travel
     * @param speed the speed at which to travel
     * @return the consumption of the squadron
     * @throw invalid_argument if the distance is negative
     * @throw invalid_argument if the speed is negative or greater than
     *                         the squadron's maximum speed
     */
    [[nodiscard]] long double getConsumption(
            long double distance,
            long double speed
    ) const;

    /**
     * Retrieve the maximum speed of the squadron
     * @return the maximum speed of the squadron
     */
    [[nodiscard]] unsigned long long getMaximumSpeed() const;

    /**
     * Retrieve the weight of the squadron
     * @return the weight of the squadron
     */
    [[nodiscard]] long double getTotalWeight() const;

    /**
     * Format the squadron's information and write it to the output stream
     * @param os the output stream to write to
     * @return the output stream
     */
    std::ostream &formatToStream(std::ostream &os) const;

private:

    /**
     * Initialize the squadron with the given newName and newLeader
     * @param newName the newName of the squadron
     * @param newLeader the newLeader of the squadron (default nullptr)
     */
    void init(const std::string &newName, const Ship *newLeader = nullptr);

    /**
     * Copy the members of the given squadron the current squadron
     * @param other the squadron to copy
     * @throw bad_alloc if memory cannot be allocated
     */
    void copyMembers(const Squadron &other);

    /**
     * Copy the members of the given squadron the current squadron
     * @param other the squadron to copy
     */
    void moveMembers(Squadron &&other);

    /**
     * Clear the squadron of all ships
     */
    void clear();

    std::string name{};
    const Ship *leader{};
    Node *head{};
};
