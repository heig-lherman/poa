#include "Policeman.hpp"

#include "../StateResponse.hpp"

Policeman::Policeman(std::string name) : Person(std::move(name)) {}

bool Policeman::canDrive() const {
    return true;
}

StateResponse Policeman::validateState(const Container&) const {
    return StateResponse::ok();
}
