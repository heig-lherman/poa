cmake_minimum_required(VERSION 3.15)
project(buffy CXX)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        src/action/Action.hpp src/action/Action.cpp
        src/action/Kill.hpp src/action/Kill.cpp
        src/action/Move.hpp src/action/Move.cpp
        src/action/Transform.hpp src/action/Transform.cpp
        src/actor/Humanoid.hpp src/actor/Humanoid.cpp
        src/actor/Human.hpp src/actor/Human.cpp
        src/actor/Vampire.hpp src/actor/Vampire.cpp
        src/actor/Buffy.hpp src/actor/Buffy.cpp
        src/displayer/FieldDisplayer.hpp src/displayer/FieldDisplayer.cpp
        src/Field.hpp src/Field.cpp
        src/Controller.hpp src/Controller.cpp
        src/math/Vector2D.hpp src/math/Vector2D.cpp
)

add_executable(buffy
        ${SOURCES}
        src/main.cpp)

if (MSVC)
    target_compile_options(buffy PRIVATE /W4 /WX)
else ()
    target_compile_options(buffy PRIVATE -Wall -Wpedantic -Werror -Wextra -Wvla -Wsign-conversion -Wconversion)
endif ()
