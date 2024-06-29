#pragma once

#include <map>
#include <memory>
#include <string>

#include "Field.hpp"

class FieldDisplayer;

/**
 * Main controller for the game.
 */
class Controller {
    struct Command;
    static const std::map<std::string, Command> COMMANDS;

public:
    /**
     * Constructor.
     * @param width the width of the fields
     * @param height the height of the fields
     * @param nbVampires the number of vampires
     * @param nbHumans the number of humans
     */
    Controller(size_t width, size_t height, unsigned nbVampires, unsigned nbHumans);

    /**
     * Starts the main loop.
     */
    void run();

    /**
     * Run a series of simulation turns and display statistics
     */
    void statistics(unsigned count) const;

    /**
     * Quit the program
     */
    void quit();

private:
    /**
     * Manage a command entered by the user
     * @param s the command to manage
     */
    void handleCommand(const std::string& s);

    /**
     * Unfold the next turn of the game
     */
    void nextTurn();

    /**
     * Display the prompt
     */
    void showPrompt() const;

    size_t _width, _height;
    unsigned _nbHumans, _nbVampires;
    unsigned _turn;
    bool _running;
    Field _gameField;
};
