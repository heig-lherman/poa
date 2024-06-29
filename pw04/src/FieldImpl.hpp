#pragma once

#include "actor/Humanoid.hpp"

template <class T>
std::shared_ptr<T> Field::findClosest(
    const std::shared_ptr<Humanoid>& searchHumanoid) const {
    auto minDistance = static_cast<double>(width() * height());
    std::shared_ptr<T> closestHumanoid;

    for (const auto& it : _humanoids) {
        const auto& humanoid = std::dynamic_pointer_cast<T>(it);
        if (humanoid != nullptr) {
            double distance = it->position().distance(searchHumanoid->position());
            if (distance < minDistance) {
                minDistance = distance;
                closestHumanoid = humanoid;
            }
        }
    }
    return closestHumanoid;
}

template <class T>
size_t Field::getCount() const {
    size_t count = 0;
    for (const auto& it : _humanoids) {
        if (std::dynamic_pointer_cast<T>(it) != nullptr) {
            count++;
        }
    }

    return count;
}
