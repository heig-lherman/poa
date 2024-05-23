#include "Bank.hpp"

#include "../person/Person.hpp"

Bank::Bank(std::string name, std::initializer_list<const Person*> people)
    : Container(std::move(name), people) {}

std::ostream& Bank::formatToStream(std::ostream& os) const {
    return Container::formatToStream(os) << listPeople();
}
