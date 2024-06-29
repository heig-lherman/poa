#include "Action.hpp"

Action::Action(const std::shared_ptr<Humanoid>& other) : _subject{other} {}

std::shared_ptr<Humanoid> Action::getSubject() const {
    return _subject.lock();
}
