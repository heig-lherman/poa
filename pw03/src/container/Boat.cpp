#include "Boat.hpp"

#include <algorithm>

#include "../StateResponse.hpp"
#include "../person/Person.hpp"

static const size_t MAX_CAPACITY = 2;

Boat::Boat(const Bank& bank, std::initializer_list<const Person*> people)
    : Container("Bateau", people), _currentBank{&bank} {}

bool Boat::isAtBank(const Bank& bank) const {
    return _currentBank == &bank;
}

void Boat::move(const Bank& bank) {
    _currentBank = &bank;
}

std::ostream& Boat::formatToStream(std::ostream& os) const {
    return Container::formatToStream(os) << " <" << listPeople() << " >";
}

StateResponse Boat::validateDrive() const {
    bool hasDriver = std::any_of(begin(), end(),
                                 [](const Person* i) { return i->canDrive(); });
    if (!hasDriver) {
        return StateResponse::nok("le bateau n'a pas de conducteur");
    }

    return StateResponse::ok();
}

StateResponse Boat::validatePeople() const {
    if (size() > MAX_CAPACITY) {
        return StateResponse::nok("le bateau a trop de personnes");
    }

    return Container::validatePeople();
}
