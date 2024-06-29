#pragma once

#include "Humanoid.hpp"

/**
 * Class representing the character Buffy.
 */
class Buffy : public Humanoid {
public:
    /**
     * Constructor.
     * @param position the position of Buffy
     */
    explicit Buffy(Vector2D position);

    char symbol() const override;

    void kill() override;

protected:
    std::unique_ptr<Action> getNextAction(const Field& field) override;
};
