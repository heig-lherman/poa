#pragma once

#include "TIEBase.hpp"
#include "../Ship.hpp"
/**
 * @file TIE.hpp
 * @brief Header file for the TIE fighter class
 */
class TIE : public TIEBase {
public:

   /**
    * Constructor for the TIE class
    */
   TIE();

   /**
    * Retrieve the ship's weight in tons
    * @return The weight of the ship
    */
   [[nodiscard]] long double getWeight() const override;

    /**
     * Retrieve the ship's maximum speed in MGLT
     * @return The maximum speed of the ship
     */
   [[nodiscard]] unsigned long long getMaximumSpeed() const override;

    /**
     * Retrieve the ship's model
     * @return The name of the ship's model
     */
   [[nodiscard]] std::string getModelName() const override;

private:
   static unsigned idCounter;
};

