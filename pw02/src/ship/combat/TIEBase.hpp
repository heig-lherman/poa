#pragma once

#include "../Ship.hpp"
/**
 * @file TIEBase.hpp
 * @brief Header file for the TIE abstract class
 */
class TIEBase : public Ship {
protected:
    /**
     * Constructor for the TIEBase class
     * @param id The ship's unique identifier
     */
    explicit TIEBase(unsigned id);

public:
    /**
     * Retrieve the ship's model
     * @return The name of the ship's model
     */
    [[nodiscard]] std::string getModelName() const override;
};
