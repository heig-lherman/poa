#include "Container.hpp"

#include <algorithm>
#include <sstream>

#include "../StateResponse.hpp"
#include "../person/Person.hpp"

Container::Container(std::string name, std::initializer_list<const Person*> people)
    : _name{std::move(name)}, _people{people} {}

std::size_t Container::size() const {
    return _people.size();
}

bool Container::contains(const Person& person) const {
    return std::find(begin(), end(), &person) != end();
}

bool Container::add(const Person& person) {
    _people.push_back(&person);
    return true;
}

bool Container::remove(const Person& person) {
    return std::erase_if(_people, [&person](const Person* i) { return i == &person; }) > 0;
}

void Container::clear() {
    _people.clear();
}

StateResponse Container::validatePeople() const {
    for (auto& it : *this) {
        const StateResponse& response = it->validateState(*this);
        if (!response.valid()) {
            return response;
        }
    }

    return StateResponse::ok();
}

std::list<const Person*>::const_iterator Container::begin() const {
    return _people.begin();
}

std::list<const Person*>::const_iterator Container::end() const {
    return _people.end();
}

std::ostream& Container::formatToStream(std::ostream& os) const {
    return os << _name << ":";
}

std::string Container::listPeople() const {
    std::ostringstream res;
    for (auto& it : *this) {
        res << " " << it->name();
    }

    return res.str();
}

std::ostream& operator<<(std::ostream& os, const Container& container) {
    return container.formatToStream(os);
}
