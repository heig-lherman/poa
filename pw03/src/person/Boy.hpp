#pragma once

#include "Child.hpp"

/**
 * @brief A boy is a child that should always be accompanied by
 *        his father when the mother is present.
 */
class Boy : public Child {
public:
    /**
     * @brief Constructor
     * @param name The name of the boy
     * @param father The father
     * @param mother The mother
     */
    Boy(std::string name, const Adult& father, const Adult& mother);

    StateResponse validateState(const Container& people) const override;
};
