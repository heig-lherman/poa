#pragma once

#include <optional>

#include "../math/Vector2D.hpp"
#include "Action.hpp"

/**
 * Action to move a character.
 */
class Move : public Action {
public:
    /**
     * Constructor.
     * @param subject The subject to move
     * @param range The number of cells the subject should move at once
     * @param destination Optionally, move towards this destination target
     */
    explicit Move(const std::shared_ptr<Humanoid>& subject,
                  unsigned range,
                  std::optional<Vector2D> destination = std::nullopt);

    /**
     * Find the cell to go to, and execute the move.
     * @param field The field on which the action will take place
     */
    void execute(Field& field) override;

private:
    unsigned _range;
    std::optional<Vector2D> _destination;
};
