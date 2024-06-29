#include <iostream>
#include <string>

#include "Controller.hpp"

static const int NB_ARGS = 5;

static unsigned parseUnsigned(const char* str) {
    if (!isdigit(str[0])) {
        throw std::exception{};
    }

    return static_cast<unsigned>(std::stoul(str));
}

/**
 * Main function of the program that runs the simulation.
 * When the program is run, it expects 4 arguments, in the following order:
 * - width of the field
 * - height of the field
 * - number of vampires
 * - number of humans
 * Once you have provided the arguments, the program will start the simulation. You will
 * be prompted to enter a command. The available commands are:
 * - n or enter: go to the next turn
 * - s: display statistics
 * - q: quit the simulation
 */
int main(int argc, char* argv[]) {
    if (argc != NB_ARGS) {
        std::cout << "Usage: " << argv[0] << " <width> <height> <nbVampires> <nbHumans>"
                  << std::endl;
        return 1;
    }

    unsigned width, height, nbHumans, nbVampires;
    try {
        width = parseUnsigned(argv[1]);
        height = parseUnsigned(argv[2]);
        nbVampires = parseUnsigned(argv[3]);
        nbHumans = parseUnsigned(argv[4]);
    } catch (std::exception& e) {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }

    if (width == 0 || height == 0 || nbHumans == 0 || nbVampires == 0) {
        std::cerr << "Parameters of the simulation cannot be 0." << std::endl;
        return 1;
    }

    Controller controller{width, height, nbVampires, nbHumans};
    controller.run();

    return 0;
}