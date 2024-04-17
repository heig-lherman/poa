/**
 * @file tests.cpp
 * @brief This file contains the tests for the Squadron class.
 */
#include <gtest/gtest.h>
#include <iostream>

#include "Squadron.hpp"
#include "ship/cargo/Shuttle.hpp"
#include "ship/cargo/StarDreadnought.hpp"
#include "ship/combat/TIE.hpp"
#include "ship/combat/TIEInterceptor.hpp"

TEST(Squadron, ConsumptionCalculation) {
    Squadron squad{"TEST"};
    Shuttle ship1(42);
    TIE ship2;
    squad += ship1;
    squad += ship2;

    // assert that the consumption is correct
    long double totalConsumption = squad.getConsumption(175.2l, 12l);
    ASSERT_NEAR(totalConsumption, 30.7333, 0.0001);

    // assert throws on invalid parameters
    ASSERT_THROW(squad.getConsumption(175.1, 60l), std::invalid_argument);
    ASSERT_THROW(squad.getConsumption(-1l, 15l), std::invalid_argument);
    ASSERT_THROW(squad.getConsumption(10l, -1l), std::invalid_argument);
}

TEST(Squadron, AddShips) {
    Squadron squad{"TEST"};
    TIE ship1;
    TIEInterceptor ship2;
    Shuttle ship3(50);
    StarDreadnought ship4(10000);

    // Try different methods of adding ships
    squad += ship1;
    squad = squad + ship2;
    squad.addShip(ship3);
    Squadron squadCopy = squad.addShipCopy(ship4);

    std::stringstream ss;

    // squad should have three ships
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 54 MGLT\ntotal weight : 421.00 "
              "tons\n-- Members :\n[TIE/LN #2]\nweight : 6.00 tons\nmax speed "
              ": 100 MGLT\n[TIE/IN #1]\nweight : 5.00 tons\nmax speed : 110 "
              "MGLT\n[Lambda-class Shuttle #2]\nweight : 410.00 tons\nmax "
              "speed : 54 MGLT\ncargo : 50.0 tons (max: 80.0)");

    // squadCopy should have 4 ships
    ss.str("");
    ss << squadCopy;
    ASSERT_EQ(
        ss.str(),
        "Squadron : TEST\nmax speed : 40 MGLT\ntotal weight : 9000010421.00 "
        "tons\n-- Members :\n[TIE/LN #2]\nweight : 6.00 tons\nmax speed : 100 "
        "MGLT\n[TIE/IN #1]\nweight : 5.00 tons\nmax speed : 110 "
        "MGLT\n[Lambda-class Shuttle #2]\nweight : 410.00 tons\nmax speed : 54 "
        "MGLT\ncargo : 50.0 tons (max: 80.0)\n[Super-class Star Destroyer "
        "#1]\nweight : 9000010000.00 tons\nmax speed : 40 MGLT\ncargo : "
        "10000.0 tons (max: 250000.0)");

    // verify that adding a ship that is already in the squadron does not add a
    // duplicate
    ss.str("");
    ss << squad + ship1;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 54 MGLT\ntotal weight : 421.00 "
              "tons\n-- Members :\n[TIE/LN #2]\nweight : 6.00 tons\nmax speed "
              ": 100 MGLT\n[TIE/IN #1]\nweight : 5.00 tons\nmax speed : 110 "
              "MGLT\n[Lambda-class Shuttle #2]\nweight : 410.00 tons\nmax "
              "speed : 54 MGLT\ncargo : 50.0 tons (max: 80.0)");
}

TEST(Squadron, RemoveShips) {
    Squadron squad{"TEST"};
    TIE ship1;
    TIEInterceptor ship2;
    Shuttle ship3(50);
    TIE ship4;
    squad += ship1;
    squad += ship2;
    squad += ship3;
    squad += ship4;

    // try out different methods
    squad -= ship1;
    squad = squad - ship2;
    squad.removeShip(ship3);
    squad = squad.removeShipCopy(ship4);

    std::stringstream ss;

    // squad should be empty
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 0 MGLT\ntotal weight : 0.00 "
              "tons\n-- Members :\nNo members");

    // verify that removing a ship that is not in the squadron does not change
    // anything
    ss.str("");
    squad -= ship1;
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 0 MGLT\ntotal weight : 0.00 "
              "tons\n-- Members :\nNo members");

    squad += ship1;
    squad += ship2;
    squad += ship3;
    squad += ship4;

    // delete a ship in the middle
    ss.str("");
    squad -= ship3;
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 100 MGLT\ntotal weight : 17.00 "
              "tons\n-- Members :\n[TIE/LN #3]\nweight : 6.00 tons\nmax speed "
              ": 100 MGLT\n[TIE/IN #2]\nweight : 5.00 tons\nmax speed : 110 "
              "MGLT\n[TIE/LN #4]\nweight : 6.00 tons\nmax speed : 100 MGLT");

    // delete the last ship
    ss.str("");
    squad -= ship4;
    ss << squad;
    ASSERT_EQ(
        ss.str(),
        "Squadron : TEST\nmax speed : 100 MGLT\ntotal weight : 11.00 tons\n-- "
        "Members :\n[TIE/LN #3]\nweight : 6.00 tons\nmax speed : 100 "
        "MGLT\n[TIE/IN #2]\nweight : 5.00 tons\nmax speed : 110 MGLT");

    // delete the first ship
    ss.str("");
    squad -= ship1;
    ss << squad;
    ASSERT_EQ(
        ss.str(),
        "Squadron : TEST\nmax speed : 110 MGLT\ntotal weight : 5.00 tons\n-- "
        "Members :\n[TIE/IN #2]\nweight : 5.00 tons\nmax speed : 110 MGLT");

    ASSERT_NO_THROW(squad - ship2);
}

TEST(Squadron, AccessShip) {
    Squadron squad{"TEST"};
    TIE ship1;
    TIEInterceptor ship2;
    Shuttle ship3(50);
    TIE ship4;
    squad += ship1;
    squad += ship2;
    squad += ship3;
    squad += ship4;

    std::stringstream ss;

    // read first
    ss << squad.get(0);
    ASSERT_EQ(ss.str(),
              "[TIE/LN #5]\nweight : 6.00 tons\nmax speed : 100 MGLT");

    // read middle
    ss.str("");
    ss << squad.get(2);
    ASSERT_EQ(ss.str(),
              "[Lambda-class Shuttle #4]\nweight : 410.00 tons\nmax speed : 54 "
              "MGLT\ncargo : 50.0 tons (max: 80.0)");

    squad.get(3).setNickname("TEST");

    // read last
    ss.str("");
    ss << squad.get(3);
    ASSERT_EQ(ss.str(),
              "TEST [TIE/LN #6]\nweight : 6.00 tons\nmax speed : 100 MGLT");

    // read out of bounds
    ASSERT_THROW(squad.get(4), std::out_of_range);
    ASSERT_THROW(squad.get(15), std::out_of_range);

    // read on const squadron
    const Squadron squad2 = squad;
    ss.str("");
    ss << squad2.get(2);
    ASSERT_EQ(ss.str(),
              "[Lambda-class Shuttle #4]\nweight : 410.00 tons\nmax speed : 54 "
              "MGLT\ncargo : 50.0 tons (max: 80.0)");
}

TEST(Squadron, CopyOperations) {
    Squadron squad1{"TEST"};
    TIE ship1;
    TIEInterceptor ship2;
    Shuttle ship3(50);
    TIE ship4;
    squad1 += ship1;
    squad1 += ship2;
    squad1 += ship3;
    squad1 += ship4;
    squad1.setLeader(ship1);

    Squadron squad2(squad1);

    std::stringstream ss1;
    std::stringstream ss2;

    // assert that the copy is correct
    ss1 << squad1;
    ss2 << squad2;
    ASSERT_EQ(ss1.str(), ss2.str());

    // assert that the copy is independent
    squad2 -= ship1;
    ss1.str("");
    ss1 << squad1;
    ss2.str("");
    ss2 << squad2;
    ASSERT_NE(ss1.str(), ss2.str());

    // assert that the leader is independent
    squad2.setLeader(ship2);
    ss1.str("");
    ss1 << squad1;
    ss2.str("");
    ss2 << squad2;
    ASSERT_NE(ss1.str(), ss2.str());

    // assert that the copy is not deep (one ship can be owned by multiple
    // squadrons)
    ss1.str("");
    ss1 << squad1;
    squad2.get(0).setNickname("TEST");
    ss2.str("");
    ss2 << squad1;
    ASSERT_NE(ss1.str(), ss2.str());

    // copy into constant squadron
    const Squadron squad3{squad1};
    ss1.str("");
    ss1 << squad1;
    ss2.str("");
    ss2 << squad3;
    ASSERT_EQ(ss1.str(), ss2.str());
}

TEST(Squadron, LeaderDefinition) {
    Squadron squad{"TEST"};
    TIE ship1;
    TIEInterceptor ship2;
    Shuttle ship3(50);
    TIE ship4;
    StarDreadnought ship5(10000);
    squad += ship1;
    squad += ship2;
    squad += ship3;
    squad += ship4;

    // set leader
    squad.setLeader(ship2);
    std::stringstream ss;
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 54 MGLT\ntotal weight : 427.00 "
              "tons\n-- Leader : \n[TIE/IN #5]\nweight : 5.00 tons\nmax speed "
              ": 110 MGLT\n-- Members :\n[TIE/LN #9]\nweight : 6.00 tons\nmax "
              "speed : 100 MGLT\n[Lambda-class Shuttle #6]\nweight : 410.00 "
              "tons\nmax speed : 54 MGLT\ncargo : 50.0 tons (max: "
              "80.0)\n[TIE/LN #10]\nweight : 6.00 tons\nmax speed : 100 MGLT");

    // remove leader, should keep leader in squadron
    squad.removeLeader();
    ss.str("");
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 54 MGLT\ntotal weight : 427.00 "
              "tons\n-- Members :\n[TIE/LN #9]\nweight : 6.00 tons\nmax speed "
              ": 100 MGLT\n[TIE/IN #5]\nweight : 5.00 tons\nmax speed : 110 "
              "MGLT\n[Lambda-class Shuttle #6]\nweight : 410.00 tons\nmax "
              "speed : 54 MGLT\ncargo : 50.0 tons (max: 80.0)\n[TIE/LN "
              "#10]\nweight : 6.00 tons\nmax speed : 100 MGLT");

    // add a new leader
    squad.setLeader(ship5);
    ss.str("");
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 40 MGLT\ntotal weight : "
              "9000010427.00 tons\n-- Leader : \n[Super-class Star Destroyer "
              "#2]\nweight : 9000010000.00 tons\nmax speed : 40 MGLT\ncargo : "
              "10000.0 tons (max: 250000.0)\n-- Members :\n[TIE/LN #9]\nweight "
              ": 6.00 tons\nmax speed : 100 MGLT\n[TIE/IN #5]\nweight : 5.00 "
              "tons\nmax speed : 110 MGLT\n[Lambda-class Shuttle #6]\nweight : "
              "410.00 tons\nmax speed : 54 MGLT\ncargo : 50.0 tons (max: "
              "80.0)\n[TIE/LN #10]\nweight : 6.00 tons\nmax speed : 100 MGLT");

    // overwrite leader, should keep active leader in squadron
    squad.setLeader(ship1);
    ss.str("");
    ss << squad;
    ASSERT_EQ(
        ss.str(),
        "Squadron : TEST\nmax speed : 40 MGLT\ntotal weight : 9000010427.00 "
        "tons\n-- Leader : \n[TIE/LN #9]\nweight : 6.00 tons\nmax speed : 100 "
        "MGLT\n-- Members :\n[TIE/IN #5]\nweight : 5.00 tons\nmax speed : 110 "
        "MGLT\n[Lambda-class Shuttle #6]\nweight : 410.00 tons\nmax speed : 54 "
        "MGLT\ncargo : 50.0 tons (max: 80.0)\n[TIE/LN #10]\nweight : 6.00 "
        "tons\nmax speed : 100 MGLT\n[Super-class Star Destroyer #2]\nweight : "
        "9000010000.00 tons\nmax speed : 40 MGLT\ncargo : 10000.0 tons (max: "
        "250000.0)");
}

TEST(Squadron, ChangeName) {
    Squadron squad{"TEST"};

    std::stringstream ss;
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : TEST\nmax speed : 0 MGLT\ntotal weight : 0.00 "
              "tons\n-- Members :\nNo members");

    squad.setName("My beautiful new name");
    ss.str("");
    ss << squad;
    ASSERT_EQ(ss.str(),
              "Squadron : My beautiful new name\nmax speed : 0 MGLT\ntotal "
              "weight : 0.00 tons\n-- Members :\nNo members");
}

TEST(CargoShip, CargoValidation) {
    // validate negative
    ASSERT_THROW(Shuttle(-42), std::invalid_argument);
    // validate too much
    ASSERT_THROW(Shuttle(100), std::invalid_argument);
    // validate correct
    ASSERT_NO_THROW(Shuttle(0));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}