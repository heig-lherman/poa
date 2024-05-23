#include <algorithm>
#include <iostream>

#include "Controller.hpp"
#include "StateResponse.hpp"
#include "container/Bank.hpp"
#include "container/Boat.hpp"
#include "utils.hpp"

using std::cin;
using std::cout;
using std::endl;

static const size_t DISPLAY_WIDTH = 58;
static const std::string DISPLAY_LINE = std::string(DISPLAY_WIDTH, '-');
static const std::string RIVER_LINE = std::string(DISPLAY_WIDTH, '=');

static const std::string INVALID_COMMAND = "### Commande invalide",
                         INVALID_PERSON = "### Personne introuvable",
                         NOT_ON_BANK = "### La personne n'est pas sur la rive",
                         NOT_ON_BOAT = "### La personne n'est pas sur le bateau",
                         WIN_MESSAGE = "Bravo, la partie est reussie !";

struct Controller::Command {
    std::string description;
    std::function<void(Controller&, std::string&)> action;
};

const std::map<std::string, Controller::Command> Controller::COMMANDS = {
    {"p", {"afficher", [](Controller& c, std::string&) { c.showState(); }}},
    {"e <nom>",
     {"embarquer <nom>",
      [](Controller& c, std::string& arg) { c.embark(c.findPerson(arg)); }}},
    {"d <nom>",
     {"debarquer <nom>",
      [](Controller& c, std::string& arg) { c.disembark(c.findPerson(arg)); }}},
    {"m", {"deplacer bateau", [](Controller& c, std::string&) { c.moveBoat(); }}},
    {"r", {"reinitialiser", [](Controller& c, std::string&) { c.reset(); }}},
    {"q", {"quitter", [](Controller& c, std::string&) { c.stop(); }}},
    {"h", {"menu", [](Controller&, std::string&) { showHelp(); }}},
};

Controller::Controller(std::initializer_list<const Person*> people)
    : _people{people},
      _leftBank{"Gauche", people},
      _boat{_leftBank},
      _rightBank{"Droite"},
      _running{false},
      _turn{0} {}

void Controller::reset() {
    _leftBank.clear();
    for (const Person* p : _people) {
        _leftBank.add(*p);
    }
    _boat.clear();
    _boat.move(_leftBank);
    _rightBank.clear();
    _turn = 0;
}

static void showBank(const Bank& bank) {
    cout << DISPLAY_LINE << "\n" << bank << "\n" << DISPLAY_LINE << "\n";
}

void Controller::showState() const {
    showBank(_leftBank);

    bool boatAtLeft = _boat.isAtBank(_leftBank);
    if (!boatAtLeft) {
        cout << RIVER_LINE << "\n";
    }

    cout << _boat << "\n";

    if (boatAtLeft) {
        cout << RIVER_LINE << "\n";
    }

    showBank(_rightBank);
    cout << std::flush;
}

void Controller::showHelp() {
    for (const auto& [key, cmd] : COMMANDS) {
        cout << key << " : " << cmd.description << "\n";
    }
    cout << std::flush;
}

void Controller::run() {
    _running = true;

    showHelp();
    showState();
    while (_running) {
        playTurn();
    }
}

void Controller::stop() {
    _running = false;
}

void Controller::playTurn() {
    cout << _turn++ << "> ";
    std::string command;
    std::getline(cin, command);

    handleCommand(command);

    if (_rightBank.size() == _people.size()) {
        cout << WIN_MESSAGE << endl;
        stop();
    }
}

const Person* Controller::findPerson(const std::string& name) const {
    auto it = std::find_if(_people.begin(), _people.end(),
                           [&name](const Person* p) { return p->name() == name; });
    return it != _people.end() ? *it : nullptr;
}

void Controller::handleCommand(const std::string& command) {
    auto split = utils::split(command, ' ');
    std::string cmd = split.first;
    std::string arg = split.second;

    auto it = std::find_if(COMMANDS.begin(), COMMANDS.end(), [&cmd](const auto& pair) {
        return utils::split(pair.first, ' ').first == cmd;
    });
    if (it == COMMANDS.end()) {
        cout << INVALID_COMMAND << endl;
        return;
    }

    it->second.action(*this, arg);
}

Bank& Controller::activeBank() {
    return _boat.isAtBank(_leftBank) ? _leftBank : _rightBank;
}

static bool checkState(const StateResponse& state) {
    if (!state.valid()) {
        cout << state << endl;
        return false;
    }

    return true;
}

static bool applyMove(const Person* person,
                      Container& from,
                      Container& to,
                      const std::string& notOnMessage) {
    if (!from.contains(*person)) {
        cout << notOnMessage << endl;
        return false;
    }

    from.remove(*person);
    to.add(*person);
    return true;
}

void Controller::movePerson(const Person* person,
                            const std::function<bool(Bank&, Boat&)>& apply) {
    if (!person) {
        cout << INVALID_PERSON << endl;
        return;
    }

    Bank bank = activeBank();
    Boat boat = _boat;
    if (!apply(bank, boat)) {
        return;  // The move could not be applied
    }

    if (checkState(bank.validatePeople().merge(boat.validatePeople()))) {
        activeBank() = std::move(bank);
        _boat = std::move(boat);
        showState();
    }
}

void Controller::embark(const Person* person) {
    movePerson(person, [&](Bank& bank, Boat& boat) {
        return applyMove(person, bank, boat, NOT_ON_BANK);
    });
}

void Controller::disembark(const Person* person) {
    movePerson(person, [&](Bank& bank, Boat& boat) {
        return applyMove(person, boat, bank, NOT_ON_BOAT);
    });
}

void Controller::moveBoat() {
    if (checkState(_boat.validateDrive())) {
        _boat.move(_boat.isAtBank(_leftBank) ? _rightBank : _leftBank);
        showState();
    }
}
