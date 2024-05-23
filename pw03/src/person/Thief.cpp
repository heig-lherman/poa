#include "Thief.hpp"

#include "../StateResponse.hpp"
#include "../container/Container.hpp"
#include "./Policeman.hpp"

Thief::Thief(std::string name, const Policeman& policeman)
    : Person(std::move(name)), _policeman(&policeman) {}

bool Thief::canDrive() const {
    return false;
}

StateResponse Thief::validateState(const Container& people) const {
    bool hasOnlySelf = people.size() == 1 && people.contains(*this);
    if (hasOnlySelf || people.contains(*_policeman)) {
        return StateResponse::ok();
    }

    return StateResponse::nok("voleur sans le policier");
}
