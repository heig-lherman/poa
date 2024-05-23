#include "Boy.hpp"

#include "../StateResponse.hpp"
#include "../container/Container.hpp"
#include "./Adult.hpp"

Boy::Boy(std::string name, const Adult& father, const Adult& mother)
    : Child(std::move(name), father, mother) {}

StateResponse Boy::validateState(const Container& people) const {
    bool hasMother = people.contains(mother());
    bool hasFather = people.contains(father());
    if (hasMother && !hasFather) {
        return StateResponse::nok("garcon avec sa mere sans son pere");
    }

    return StateResponse::ok();
}
