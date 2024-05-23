#pragma once

#include "Person.hpp"

class Adult;

/**
 * @brief A child is a person that by default cannot drive,
 *        and has a father and a mother.
 */
class Child : public Person {
protected:
    /**
     * @brief Constructor
     * @param name name of the child
     * @param father father of the child
     * @param mother mother of the child
     */
    Child(std::string name, const Adult& father, const Adult& mother);

    /** @return the father of the child */
    const Adult& father() const;

    /** @return the mother of the child */
    const Adult& mother() const;

public:
    /** By default, children cannot drive. */
    bool canDrive() const override;

private:
    const Adult* _father;
    const Adult* _mother;
};
