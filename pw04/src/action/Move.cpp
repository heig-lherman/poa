#include "Move.hpp"

#include <iostream>
#include <vector>

#include "../Field.hpp"

Move::Move(const std::shared_ptr<Humanoid>& humanoid,
           unsigned int range,
           std::optional<Vector2D> destination)
    : Action(humanoid), _range{range}, _destination{destination} {}

static std::optional<Vector2D> getRandomDirection(Field& field,
                                                  const Vector2D& currentPosition) {
    std::vector<Vector2D> nextPositions{};
    nextPositions.reserve(8);

    int maxX = static_cast<int>(field.width());
    int maxY = static_cast<int>(field.height());
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            int x = currentPosition.x() + i;
            int y = currentPosition.y() + j;

            if (x < 0 || x >= maxX || y < 0 || y >= maxY) {
                continue;
            }

            nextPositions.emplace_back(i, j);
        }
    }

    if (nextPositions.empty()) {
        return std::nullopt;
    }

    std::uniform_int_distribution<size_t> pos(0, nextPositions.size() - 1);
    return nextPositions[pos(field.random())];
}

void Move::execute(Field& field) {
    Vector2D position = getSubject()->position();

    for (unsigned i = 0; i < _range; ++i) {
        position.add(
            _destination
                .transform([&](const Vector2D& v) { return position.direction(v); })
                .or_else([&] { return getRandomDirection(field, position); })
                .value_or(Vector2D(0, 0)));
    }

    getSubject()->move(position);
}