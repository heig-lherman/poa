#include "Transform.hpp"

#include "../Field.hpp"
#include "../actor/Vampire.hpp"

Transform::Transform(const std::shared_ptr<Humanoid>& humanoid) : Kill(humanoid) {}

void Transform::execute(Field& field) {
    const auto& subject = getSubject();

    // Make sure the subject is still alive before adding another vampire, so that we
    // avoid adding a vampire to the field if the subject has already been transformed by
    // another vampire targeting the same subject.
    std::bernoulli_distribution success(0.5);
    if (success(field.random()) && subject->alive()) {
        field.addHumanoid(std::make_shared<Vampire>(subject->position()));
    }

    Kill::execute(field);
}
