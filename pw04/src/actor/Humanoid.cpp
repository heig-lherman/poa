#include "Humanoid.hpp"

Humanoid::Humanoid(Vector2D position) : _alive{true}, _position{position} {}

bool Humanoid::alive() const {
    return _alive;
}

const Vector2D& Humanoid::position() const {
    return _position;
}

void Humanoid::move(const Vector2D& position){
    _position = position;
}

void Humanoid::kill() {
    _alive = false;
}

void Humanoid::createAction(const Field& field) {
    if (_nextAction) {
        return;
    }

    _nextAction = getNextAction(field);
}

void Humanoid::executeAction(Field& field) {
    if (_nextAction) {
        _nextAction->execute(field);
        _nextAction.reset();
    }
}
