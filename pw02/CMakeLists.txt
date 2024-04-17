cmake_minimum_required(VERSION 3.10)
project(LabSquadron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
        src/Squadron.hpp src/Squadron.cpp
        src/ship/Ship.hpp src/ship/Ship.cpp
        src/ship/cargo/Shuttle.hpp src/ship/cargo/Shuttle.cpp
        src/ship/cargo/StarDreadnought.hpp src/ship/cargo/StarDreadnought.cpp
        src/ship/combat/TIE.hpp src/ship/combat/TIE.cpp
        src/ship/combat/TIEInterceptor.hpp src/ship/combat/TIEInterceptor.cpp
        src/ship/combat/TIEBase.hpp src/ship/combat/TIEBase.cpp
        src/ship/cargo/CargoShip.cpp src/ship/cargo/CargoShip.hpp
)

add_executable(squadron ${SOURCES} src/main.cpp)

find_library(GTEST gtest)
if (NOT GTEST)
    message("GoogleTest not found, testing executable will not be built")
else ()
    add_executable(tests ${SOURCES} src/tests.cpp)
    target_compile_definitions(tests PRIVATE TESTING=1)
    target_link_libraries(tests ${GTEST})
endif ()

if(MSVC)
    target_compile_options(squadron PRIVATE /W4 /WX)
else()
    target_compile_options(squadron PRIVATE -Wall -Wpedantic -Werror -Wextra)
endif()