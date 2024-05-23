#pragma once

#include "Container.hpp"

class Bank;

/**
 * @brief A boat is a container that can contain a limited set of people
 */
class Boat : public Container {
public:
    /**
     * Construct a boat with no people
     * @param currentBank the bank where the boat is
     * @param people people to add to the container
     */
    explicit Boat(const Bank& currentBank,
                  std::initializer_list<const Person*> people = {});

    /**
     * Check if the boat is at a given bank
     * @param bank the bank to check
     * @return whether the boat is at the given bank
     */
    bool isAtBank(const Bank& bank) const;

    /**
     * Set the bank where the boat is, if the boat has a driver
     * @param bank the bank where the boat is
     * @return whether the bank was set successfully
     */
    void move(const Bank& bank);

    /** @return reason if the boat cannot be driven */
    StateResponse validateDrive() const;

    StateResponse validatePeople() const override;

    std::ostream& formatToStream(std::ostream& os) const override;

private:
    const Bank* _currentBank;
};
