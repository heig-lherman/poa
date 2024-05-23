#pragma once

#include "Person.hpp"

class Policeman;

/**
 * @brief A thief is a person that can't drive and should always be
 *        accompanied by an assigned policeman.
 */
class Thief : public Person {
public:
    /**
     * @breif Constructor
     * @param name The name of the thief
     * @param policeman The policeman assigned to the thief
     */
    Thief(std::string name, const Policeman& policeman);

    bool canDrive() const override;

    StateResponse validateState(const Container& people) const override;

private:
    const Policeman* _policeman;
};
