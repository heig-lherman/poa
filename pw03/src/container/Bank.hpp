#pragma once

#include "Container.hpp"

/**
 * @brief A bank is a container that can contain an unlimited amount of people
 */
class Bank : public Container {
public:
    /**
     * @brief Constructor
     * @param name the name of the bank
     * @param people the people to add to the bank
     */
    explicit Bank(std::string name,
                  std::initializer_list<const Person*> people = {});

    std::ostream& formatToStream(std::ostream& os) const override;
};
