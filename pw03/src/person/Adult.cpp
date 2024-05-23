#include "Adult.hpp"

#include "../StateResponse.hpp"

Adult::Adult(std::string name) : Person(std::move(name)) {}

bool Adult::canDrive() const {
    return true;
}

StateResponse Adult::validateState(const Container&) const {
    return StateResponse::ok();
}
