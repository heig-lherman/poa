#pragma once

#include "Child.hpp"

/**
 * @brief A girl is a child that should always be accompanied by
 *        her mother when the father is present.
 */
class Girl : public Child {
public:
    /**
     * @brief Constructor
     * @param name The name of the girl
     * @param father The assigned father
     * @param mother The assigned mother
     */
    Girl(std::string name, const Adult& father, const Adult& mother);

    StateResponse validateState(const Container& people) const override;
};
