#include "Child.hpp"

Child::Child(std::string name, const Adult& father, const Adult& mother)
    : Person(std::move(name)), _father(&father), _mother(&mother) {}

bool Child::canDrive() const {
    return false;
}

const Adult& Child::father() const {
    return *_father;
}

const Adult& Child::mother() const {
    return *_mother;
}
