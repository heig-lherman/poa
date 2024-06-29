#pragma once

#include <memory>

#include "../action/Action.hpp"
#include "../math/Vector2D.hpp"

class Field;

/**
 * Abstract class representing humanoids.
 */
class Humanoid : public std::enable_shared_from_this<Humanoid> {
public:
    /**
     * Destructor for polymorphism.
     */
    virtual ~Humanoid() noexcept = default;

    /**
     * Get the symbol of the humanoid.
     * @return the symbol of the humanoid
     */
    virtual char symbol() const = 0;

    /**
     * @return true if the humanoid is alive, false otherwise
     */
    bool alive() const;

    /**
     * Get the position of the humanoid.
     * @return the new position of the humanoid
     */
    const Vector2D& position() const;

    /**
     * Kill the humanoid
     */
    virtual void kill();

    /**
     * Move the humanoid.
     * @param newPosition the new position of the humanoid
     */
    void move(const Vector2D& position);

    /**
     * Set the next action of the humanoid.
     * @param field the field on which the action will take place
     */
    void createAction(const Field& field);

    /**
     * Execute the next action of the humanoid.
     * @param field the field on which the action will take place
     */
    void executeAction(Field& field);

protected:
    /**
     * Constructor.
     * @param position the position of the humanoid
     */
    explicit Humanoid(Vector2D position);

    /**
     * Compute the next action of the humanoid.
     * @param field the field on which the action will take place
     * @return the next action of the humanoid
     */
    virtual std::unique_ptr<Action> getNextAction(const Field& field) = 0;

private:
    bool _alive;
    Vector2D _position;

    std::unique_ptr<Action> _nextAction;
};
