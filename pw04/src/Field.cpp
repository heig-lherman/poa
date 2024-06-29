#include "Field.hpp"

#include "actor/Buffy.hpp"
#include "actor/Human.hpp"
#include "actor/Humanoid.hpp"
#include "actor/Vampire.hpp"

// Static random device for seeding fields
static std::random_device rd;

Field::Field(size_t width, size_t height, unsigned nbVampires, unsigned nbHumans)
    : _width{width}, _height{height}, _turn{0}, _humanoids{}, _gen{rd()} {
    if (width == 0 || height == 0 || nbHumans == 0 || nbVampires == 0) {
        throw std::invalid_argument("Parameters of the simulation cannot be 0.");
    }

    std::uniform_int_distribution<int> wd(0, static_cast<int>(_width) - 1);
    std::uniform_int_distribution<int> hd(0, static_cast<int>(_height) - 1);
    addHumanoid(std::make_shared<Buffy>(Vector2D(wd(_gen), hd(_gen))));

    for (unsigned i = 0; i < nbVampires; i++) {
        addHumanoid(std::make_shared<Vampire>(Vector2D(wd(_gen), hd(_gen))));
    }

    for (unsigned i = 0; i < nbHumans; i++) {
        addHumanoid(std::make_shared<Human>(Vector2D(wd(_gen), hd(_gen))));
    }
}

unsigned Field::nextTurn() {
    // Determine next actions
    for (const auto& _humanoid : _humanoids) {
        _humanoid->createAction(*this);
    }

    // Execute actions
    for (const auto& _humanoid : _humanoids) {
        _humanoid->executeAction(*this);
    }

    // Remove killed humanoids
    erase_if(_humanoids, [](const auto& humanoid) { return !humanoid->alive(); });

    return _turn++;
}

size_t Field::width() const {
    return _width;
}

size_t Field::height() const {
    return _height;
}

void Field::addHumanoid(const std::shared_ptr<Humanoid>& humanoid) {
    _humanoids.emplace_back(humanoid);
}

std::shared_ptr<Humanoid> Field::at(const Vector2D& position) const {
    for (const auto& humanoid : _humanoids) {
        if (humanoid->position().equals(position)) {
            return humanoid;
        }
    }

    return nullptr;
}

std::mt19937& Field::random() {
    return _gen;
}
