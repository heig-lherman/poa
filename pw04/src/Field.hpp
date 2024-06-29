#pragma once

#include <list>
#include <memory>
#include <random>

#include "math/Vector2D.hpp"

class Humanoid;

/**
 * Field representing the game cells.
 */
class Field {
public:
    /**
     * Constructor.
     * @param width The width of the field
     * @param height The height of the field
     * @param nbVampires The number of vampires to spawn
     * @param nbHumans The number of humans to spawn
     * @throw std::invalid_argument if one of the parameters is 0
     */
    Field(size_t width, size_t height, unsigned nbVampires, unsigned nbHumans);

    /**
     * Simulate a turn of the simulation
     * @return the number of the next turn
     */
    unsigned nextTurn();

    /**
     * Get the height of the field
     * @return the height of the field
     */
    size_t height() const;

    /**
     * Get the width of the game
     * @return the width of the game
     */
    size_t width() const;

    /**
     * Add a humanoid to the field
     * @param humanoid the humanoid to add
     */
    void addHumanoid(const std::shared_ptr<Humanoid>& humanoid);

    /**
     * Get the humanoid at a given position
     * @param position the position to check
     * @return the humanoid at the given position if it exists, nullptr otherwise
     */
    std::shared_ptr<Humanoid> at(const Vector2D& position) const;

    /**
     * Find the closest humanoid of a given type
     * @tparam T the type of humanoid to find
     * @param humanoid the humanoid from which to search
     * @return the closest humanoid of the given type
     */
    template <class T>
    std::shared_ptr<T> findClosest(const std::shared_ptr<Humanoid>& searchHumanoid) const;

    /**
     * Get the number of humanoids of a given type
     * @tparam T the type of humanoid to count
     * @return the number of humanoids of the given type
     */
    template <class T>
    size_t getCount() const;

    /**
     * Get the random engine for field operations
     * @return the random engine
     */
    std::mt19937& random();

private:
    size_t _width;
    size_t _height;
    unsigned _turn;

    std::list<std::shared_ptr<Humanoid>> _humanoids;
    std::mt19937 _gen;
};

#include "./FieldImpl.hpp"
