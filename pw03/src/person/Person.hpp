#pragma once

#include <string>

class Container;
class StateResponse;

/**
 * @brief Person represents a person with a name.
 */
class Person {
protected:
    /**
     * Constructor for a Person
     * @param name The name of the person
     */
    explicit Person(std::string name);

public:
    /** Virtual default destructor to allow for polymorphism */
    virtual ~Person() noexcept = default;

    /** @return The name of the person */
    std::string_view name() const;

    /** @return Whether the person can drive */
    virtual bool canDrive() const = 0;

    /** @return Whether the person can stay with a given list of people */
    virtual StateResponse validateState(const Container& people) const = 0;

private:
    std::string _name;
};
