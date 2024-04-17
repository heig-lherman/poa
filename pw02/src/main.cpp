/**
 * @file main.cpp
 * @brief Entry point for the application that handles the creation of a
 * squadron and the addition of ships to it, with a basic display of the
 * contents.
 * @since 2024-04-17
 */
#include <iostream>
#include "Squadron.hpp"
#include "ship/cargo/Shuttle.hpp"
#include "ship/combat/TIE.hpp"

using namespace std;

int main() {
    TIE blackLeader;
    blackLeader.setNickname("Black Leader");
    TIE blackTwo;
    Shuttle shuttle(23.4);  // 23.4 tonnes de marchandises
    Squadron squad("Black Squadron");
    squad += blackLeader;
    squad += blackTwo;
    squad += shuttle;
    squad.setLeader(blackLeader);
    cout << squad << endl;

    return EXIT_SUCCESS;
}