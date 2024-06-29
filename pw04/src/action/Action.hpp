#pragma once

#include <memory>

class Field;
class Humanoid;

/**
 * Base class for all actions.
 */
class Action {
public:
    /**
     * Destructor for polymorphism.
     */
    virtual ~Action() noexcept = default;

    /**
     * Execute the current action while modifying the field
     * @param field the field on which the action will take place
     */
    virtual void execute(Field& field) = 0;

protected:
    /**
     * Constructor for the action
     * @param subject the subject of the action
     */
    explicit Action(const std::shared_ptr<Humanoid>& subject);

    /**
     * Get the humanoid that is the subject of the action
     * @return the humanoid that is the subject of the action
     */
    [[nodiscard]] std::shared_ptr<Humanoid> getSubject() const;

private:
    std::weak_ptr<Humanoid> _subject;
};
