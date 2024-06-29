#pragma once

#include "Action.hpp"

/**
 * Action to kill a character.
 */
class Kill : public Action {
public:
    /**
     * Constructor.
     * @param subject the subject to kill
     */
    explicit Kill(const std::shared_ptr<Humanoid>& subject);

    /**
     * Kill the humanoid.
     */
    void execute(Field&) override;
};
