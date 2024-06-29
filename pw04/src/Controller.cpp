#include "Controller.hpp"

#include <functional>
#include <iostream>

#include "displayer/FieldDisplayer.hpp"
#include "actor/Human.hpp"
#include "actor/Vampire.hpp"

using std::cout;
using std::endl;

static const std::string DEFAULT_COMMAND_KEY = "n";

struct Controller::Command {
    std::string usage;
    std::function<void(Controller&)> action;
};

const std::map<std::string, Controller::Command> Controller::COMMANDS = {
    {"n", {"n>ext", [](Controller& c) { c.nextTurn(); }}},
    {"s", {"s>tatistics", [](Controller& c) { c.statistics(10000); }}},
    {"q", {"q>uit", [](Controller& c) { c.quit(); }}}};

Controller::Controller(size_t width,
                       size_t height,
                       unsigned int nbVampires,
                       unsigned int nbHumans)
    : _width{width},
      _height{height},
      _nbHumans{nbHumans},
      _nbVampires{nbVampires},
      _turn{0},
      _running{true},
      _gameField{width, height, nbVampires, nbHumans} {}

static std::string getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
        return DEFAULT_COMMAND_KEY;
    }

    return input;
}

void Controller::showPrompt() const {
    cout << "[" << _turn << "]";
    for (const auto& [_, command] : COMMANDS) {
        cout << " " << command.usage;
    }
    cout << ": " << std::flush;
}

void Controller::run() {
    // display the field for the first time
    FieldDisplayer::display(_gameField);

    while (_running) {
        showPrompt();
        handleCommand(getUserInput());
    }
}

void Controller::quit() {
    _running = false;
}

void Controller::handleCommand(const std::string& s) {
    if (!COMMANDS.contains(s)) {
        std::cout << "Invalid command" << std::endl;
        return;
    }

    COMMANDS.at(s).action(*this);
}

void Controller::nextTurn() {
    _turn = _gameField.nextTurn();
    FieldDisplayer::display(_gameField);
}

void Controller::statistics(unsigned count) const {
    unsigned nbWon = 0;
    for (unsigned i = 0; i < count; i++) {
        Field simulationField{_width, _height, _nbVampires, _nbHumans};

        while (simulationField.getCount<Vampire>() > 0) {
            simulationField.nextTurn();
        }

        if (simulationField.getCount<Human>() > 0) {
            nbWon++;
        }

        if (i % 1000 == 0) {
            cout << (static_cast<double>(i) / count) * 100 << "% complete" << endl;
        }
    }

    cout << "Percentage of simulations won by Buffy: "
         << ((static_cast<double>(nbWon) / count)) * 100 << " %" << endl;
}
