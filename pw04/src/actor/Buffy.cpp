#include "Buffy.hpp"

#include "../Field.hpp"
#include "../action/Kill.hpp"
#include "../action/Move.hpp"
#include "Vampire.hpp"

static constexpr unsigned RANDOM_RANGE = 1, ATTACK_RANGE = 1, TARGET_RANGE = 2;

Buffy::Buffy(Vector2D position) : Humanoid(position) {}

char Buffy::symbol() const {
    return 'B';
}

void Buffy::kill() {
    // Prevent buffy from being killed
}

std::unique_ptr<Action> Buffy::getNextAction(const Field& field) {
    auto vampire = field.findClosest<Vampire>(shared_from_this());
    if (!vampire) {
        return std::make_unique<Move>(shared_from_this(), RANDOM_RANGE);
    }

    if (position().distance(vampire->position()) <= ATTACK_RANGE) {
        return std::make_unique<Kill>(vampire);
    }

    return std::make_unique<Move>(shared_from_this(), TARGET_RANGE, vampire->position());
}
