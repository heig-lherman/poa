#pragma once

#include "Humanoid.hpp"

/**
 * Class representing humans.
 */
class Human : public Humanoid {
public:
    /**
     * Constructor.
     * @param position the position of the human
     */
    explicit Human(Vector2D position);

    char symbol() const override;

protected:
    std::unique_ptr<Action> getNextAction(const Field&) override;
};
