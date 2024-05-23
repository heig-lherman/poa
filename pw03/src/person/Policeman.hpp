#pragma once

#include "Person.hpp"

/**
 * @brief The policeman is a person that can drive and
 *        can be assigned to a thief.
 */
class Policeman : public Person {
public:
    /**
     * @brief Constructor
     * @param name name of the policeman
     */
    explicit Policeman(std::string name);

    bool canDrive() const override;

    StateResponse validateState(const Container& people) const override;
};
