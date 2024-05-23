#include "Person.hpp"

Person::Person(std::string name) : _name(std::move(name)) {}

std::string_view Person::name() const {
    return _name;
}
