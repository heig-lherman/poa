#pragma once

#include "Humanoid.hpp"

/**
 * Class representing vampires.
 */
class Vampire : public Humanoid {
public:
    /**
     * Constructor.
     * @param position the position of the vampire
     */
    explicit Vampire(Vector2D position);

    char symbol() const override;

protected:
    std::unique_ptr<Action> getNextAction(const Field& field) override;
};
