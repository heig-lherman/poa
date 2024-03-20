cmake_minimum_required(VERSION 3.10)
project(LabMatrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES src/Matrix.cpp src/Matrix.hpp src/Operators.cpp src/Operators.hpp src/Utils.cpp src/Utils.hpp)

add_executable(matrix ${SOURCES} src/main.cpp)

find_library(GTEST gtest)
if (NOT GTEST)
    message("GoogleTest not found, testing executable will not be built")
else ()
    add_executable(tests ${SOURCES} src/tests.cpp)
    target_compile_definitions(tests PRIVATE TESTING=1)
    target_link_libraries(tests ${GTEST})
endif ()

if(MSVC)
    target_compile_options(matrix PRIVATE /W4 /WX)
else()
    target_compile_options(matrix PRIVATE -Wall -Wpedantic -Werror)
endif()
