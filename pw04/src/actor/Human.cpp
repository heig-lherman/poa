#include "Human.hpp"

#include "../action/Move.hpp"
#include "../Field.hpp"

static constexpr unsigned MOVE_RANGE = 1;

Human::Human(Vector2D position) : Humanoid(position) {}

char Human::symbol() const {
    return 'h';
}

std::unique_ptr<Action> Human::getNextAction(const Field&) {
    return std::make_unique<Move>(shared_from_this(), MOVE_RANGE);
}
