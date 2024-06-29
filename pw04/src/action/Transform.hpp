#pragma once

#include "Kill.hpp"

/**
 * Action to transform a character.
 */
class Transform : public Kill {
public:
    /**
     * Constructor.
     * @param subject the subject to transform
     */
    explicit Transform(const std::shared_ptr<Humanoid>& subject);

    /**
     * Kill the humanoid and transform it.
     * @param field the field on which the action will take place
     */
    void execute(Field& field) override;
};
