/**
 * @file Squadron.cpp
 * @brief Implementation of the Squadron class
 */
#include "Squadron.hpp"
#include <cmath>
#include <iomanip>

struct Squadron::Node {
    Ship* const ship;
    Node* next;
};

std::ostream& operator<<(std::ostream& os, const Squadron& squadron) {
    return squadron.formatToStream(os);
}

Squadron operator+(const Squadron& squadron, Ship& ship) {
    return squadron.addShipCopy(ship);
}

Squadron operator-(const Squadron& squadron, const Ship& ship) {
    return squadron.removeShipCopy(ship);
}

Squadron::Squadron(const std::string& name) {
    init(name);
}

Squadron::Squadron(const Squadron& other) {
    init(other.name, other.leader);
    copyMembers(other);
}

Squadron::Squadron(Squadron&& other) noexcept {
    init(other.name, other.leader);
    moveMembers(std::move(other));
}

Squadron::~Squadron() noexcept {
    clear();
}

Squadron& Squadron::operator=(const Squadron& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    init(other.name, other.leader);
    copyMembers(other);

    return *this;
}

Squadron& Squadron::operator=(Squadron&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();
    init(other.name, other.leader);
    moveMembers(std::move(other));

    return *this;
}

Squadron& Squadron::operator+=(Ship& ship) {
    return addShip(ship);
}

Squadron& Squadron::operator-=(const Ship& ship) {
    return removeShip(ship);
}

void Squadron::setName(const std::string& newName) {
    name = newName;
}

void Squadron::setLeader(Ship& ship) {
    if (leader && leader == &ship) {
        return;
    }

    addShip(ship);
    leader = &ship;
}

void Squadron::removeLeader() {
    leader = nullptr;
}

Ship& Squadron::get(size_t index) const {
    Node* current = head;
    for (unsigned int i = 0; i < index; i++) {
        if (!current || !current->next) {
            throw std::out_of_range("Index out of bounds");
        }

        current = current->next;
    }

    return *current->ship;
}

long double Squadron::getConsumption(long double distance,
                                     long double speed) const {
    if (speed < 0 || distance < 0) {
        throw std::invalid_argument("Speed and distance must be positive");
    }

    if (speed > getMaximumSpeed()) {
        throw std::invalid_argument(
            "Speed must be less than the squadron's maximum speed");
    }

    long double weight = getTotalWeight();
    return std::cbrt(weight) / 2 * log10l(weight * speed) *
           log10l(distance + 1);
}

Squadron Squadron::addShipCopy(Ship& ship) const {
    return Squadron(*this).addShip(ship);
}

Squadron& Squadron::addShip(Ship& ship) {
    Node* current = head;
    while (current && current->next) {
        if (current->ship == &ship || current->next->ship == &ship) {
            return *this;
        }
        current = current->next;
    }

    Node* newNode = new Node{&ship, nullptr};
    if (current) {
        current->next = newNode;
    } else {
        head = newNode;
    }

    return *this;
}

Squadron Squadron::removeShipCopy(const Ship& ship) const {
    return Squadron(*this).removeShip(ship);
}

Squadron& Squadron::removeShip(const Ship& ship) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr && current->ship != &ship) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return *this;
    }

    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    if (current->ship == leader) {
        removeLeader();
    }

    delete current;

    return *this;
}

std::ostream& Squadron::formatToStream(std::ostream& os) const {
    os << "Squadron : " << name << "\n";
    os << "max speed : " << getMaximumSpeed() << " MGLT\n";
    os << "total weight : " << std::fixed << std::setprecision(2)
       << getTotalWeight() << " tons\n";

    if (leader != nullptr) {
        os << "-- Leader : \n";
        os << *leader << "\n";
    }

    os << "-- Members :";
    if (!head) {
        os << "\nNo members";
        return os;
    }

    Node* current = head;
    while (current) {
        if (current->ship != leader) {
            os << "\n" << *current->ship;
        }
        current = current->next;
    }

    return os;
}

unsigned long long Squadron::getMaximumSpeed() const {
    if (!head) {
        return 0;
    }

    unsigned long long maxSpeed = head->ship->getMaximumSpeed();

    Node* current = head->next;
    while (current) {
        if (current->ship->getMaximumSpeed() < maxSpeed) {
            maxSpeed = current->ship->getMaximumSpeed();
        }

        current = current->next;
    }

    return maxSpeed;
}

long double Squadron::getTotalWeight() const {
    long double totalWeight = 0;

    Node* current = head;
    while (current) {
        totalWeight += current->ship->getWeight();
        current = current->next;
    }

    return totalWeight;
}

void Squadron::init(const std::string& newName, const Ship* newLeader) {
    name = newName;
    leader = newLeader;
    head = nullptr;
}

void Squadron::copyMembers(const Squadron& other) {
    try {
        Node* current = other.head;
        while (current) {
            addShip(*current->ship);
            current = current->next;
        }
    } catch (std::bad_alloc& e) {
        clear();
        throw;
    }
}

void Squadron::moveMembers(Squadron&& other) {
    head = other.head;
    other.head = nullptr;
}

void Squadron::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
