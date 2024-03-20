#include "Utils.hpp"

unsigned floorMod(const long num, const unsigned mod) {
    return static_cast<unsigned>((num % mod + mod) % mod);
}
