#include "Kill.hpp"

#include "../actor/Humanoid.hpp"

Kill::Kill(const std::shared_ptr<Humanoid>& humanoid) : Action(humanoid) {}

void Kill::execute(Field&) {
    getSubject()->kill();
}
