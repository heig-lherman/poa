#include "Girl.hpp"

#include "../StateResponse.hpp"
#include "../container/Container.hpp"
#include "./Adult.hpp"

Girl::Girl(std::string name, const Adult& father, const Adult& mother)
    : Child(std::move(name), father, mother) {}

StateResponse Girl::validateState(const Container& people) const {
    bool hasMother = people.contains(mother());
    bool hasFather = people.contains(father());
    if (hasFather && !hasMother) {
        return StateResponse::nok("fille avec son pere sans sa mere");
    }

    return StateResponse::ok();
}
