#pragma once

#include <functional>
#include <list>
#include <map>

#include "container/Bank.hpp"
#include "container/Boat.hpp"
#include "person/Person.hpp"

/**
 * @brief The main controller that manages the game
 */
class Controller {
    struct Command;
    static const std::map<std::string, Command> COMMANDS;

public:
    /**
     * @brief Constructor
     * @param people The people to play the game with
     */
    Controller(std::initializer_list<const Person*> people);

    /** @brief Runs the game loop */
    void run();

    /** @brief Stops the game loop */
    void stop();

private:
    void handleCommand(const std::string& command);

    const Person* findPerson(const std::string& name) const;

    void playTurn();

    void reset();

    Bank& activeBank();

    void movePerson(const Person* person, const std::function<bool(Bank&, Boat&)>& apply);

    void embark(const Person* person);

    void disembark(const Person* person);

    void moveBoat();

    void showState() const;

    static void showHelp();

    // Holds all the people in the game
    std::list<const Person*> _people;

    Bank _leftBank;
    Boat _boat;
    Bank _rightBank;

    bool _running;
    unsigned _turn;
};
