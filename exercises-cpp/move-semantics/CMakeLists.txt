add_executable(vector_move vectormove.cpp)


# Set compiler options to disable copy elision for these targets
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_executable(vector_move_no_copy_elision vectormove.cpp)
    target_compile_options(vector_move_no_copy_elision PRIVATE "-fno-elide-constructors")
endif()

