#include "Vampire.hpp"

#include "../Field.hpp"
#include "../action/Kill.hpp"
#include "../action/Move.hpp"
#include "../action/Transform.hpp"
#include "Human.hpp"

static constexpr unsigned ATTACK_RANGE = 1, MOVE_RANGE = 1;

Vampire::Vampire(Vector2D position) : Humanoid(position) {}

char Vampire::symbol() const {
    return 'V';
}

std::unique_ptr<Action> Vampire::getNextAction(const Field& field) {
    std::shared_ptr<Human> human = field.findClosest<Human>(shared_from_this());
    if (!human) {
        return nullptr;
    }

    if (position().distance(human->position()) > ATTACK_RANGE) {
        return std::make_unique<Move>(shared_from_this(), MOVE_RANGE, human->position());
    }

    return std::make_unique<Transform>(human);
}
