#pragma once

#include "Person.hpp"

/**
 * @brief An adult is a generic person that can drive and doesn't have any
 *        state constraints, can be defined as the parent of a child.
 */
class Adult : public Person {
public:
    /**
     * @brief Constructor
     * @param name The name of the adult
     */
    explicit Adult(std::string name);

    bool canDrive() const override;

    StateResponse validateState(const Container& people) const override;
};
