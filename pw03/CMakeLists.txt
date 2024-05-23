cmake_minimum_required(VERSION 3.15)
project(river CXX)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        src/Controller.hpp src/Controller.cpp
        src/container/Container.hpp src/container/Container.cpp
        src/container/Bank.hpp src/container/Bank.cpp
        src/container/Boat.hpp src/container/Boat.cpp
        src/person/Person.hpp src/person/Person.cpp
        src/person/Adult.hpp src/person/Adult.cpp
        src/person/Child.hpp src/person/Child.cpp
        src/person/Boy.hpp src/person/Boy.cpp
        src/person/Girl.hpp src/person/Girl.cpp
        src/person/Policeman.hpp src/person/Policeman.cpp
        src/person/Thief.hpp src/person/Thief.cpp
        src/StateResponse.hpp src/StateResponse.cpp
        src/utils.hpp src/utils.cpp
)

add_executable(river ${SOURCES} src/main.cpp)

if(MSVC)
    target_compile_options(river PRIVATE /W4 /WX)
else()
    target_compile_options(river PRIVATE -Wall -Wpedantic -Werror -Wextra -Wvla -Wsign-conversion -Wconversion)
endif()
