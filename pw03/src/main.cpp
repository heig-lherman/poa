#include <memory>

#include "Controller.hpp"
#include "person/Adult.hpp"
#include "person/Boy.hpp"
#include "person/Girl.hpp"
#include "person/Policeman.hpp"
#include "person/Thief.hpp"

/**
 * Main function for the river game, where a family of a father, a mother,
 * two boys and two girls, as well as a thief and a policeman have to cross the
 * river with a boat that can only carry two people at a time, and where rules
 * apply on the thief and the children.
 *
 * The game ends when everyone is on the right bank.
 */
int main() {
    // The controller will have non-owning pointers to the people, so we
    // initialize them with std::make_unique to ensure they are properly
    // managed, and then pass the raw pointers to the controller.
    auto father = std::make_unique<Adult>("pere");
    auto mother = std::make_unique<Adult>("mere");
    auto boy1 = std::make_unique<Boy>("paul", *father, *mother);
    auto boy2 = std::make_unique<Boy>("pierre", *father, *mother);
    auto girl1 = std::make_unique<Girl>("julie", *father, *mother);
    auto girl2 = std::make_unique<Girl>("jeanne", *father, *mother);
    auto policeman = std::make_unique<Policeman>("policier");
    auto thief = std::make_unique<Thief>("voleur", *policeman);

    Controller controller{father.get(),    mother.get(), boy1.get(),
                          boy2.get(),      girl1.get(),  girl2.get(),
                          policeman.get(), thief.get()};

    // Blocking function, will return when the game is over
    controller.run();
}